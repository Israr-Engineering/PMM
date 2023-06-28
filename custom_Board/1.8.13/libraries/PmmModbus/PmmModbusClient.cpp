/*
  This file is part of the ArduinoModbus library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <errno.h>

#include "PmmModbusClient.h"

PmmModbusClient::PmmModbusClient(unsigned long defaultTimeout) :
  _mb(NULL),
  _timeout(defaultTimeout),
  _defaultId(0x00),
  _transmissionBegun(false),
  _values(NULL),
  _available(0),
  _read(0),
  _availableForWrite(0),
  _written(0)
{
}

PmmModbusClient::~PmmModbusClient()
{
  if (_values != NULL) {
    free(_values);
  }

  if (_mb != NULL) {
    modbus_free(_mb);
  }
}

int PmmModbusClient::begin(modbus_t* mb, int defaultId)
{
  end();

  _mb = mb;
  _defaultId = defaultId;
  if (_mb == NULL) {
    return 0;
  }

  if (modbus_connect(_mb) != 0) {
    modbus_free(_mb);

    _mb = NULL;
    return 0;
  }

  _transmissionBegun = false;
  _available = 0;
  _read = 0;
  _availableForWrite = 0;
  _written = 0;

  modbus_set_error_recovery(_mb, MODBUS_ERROR_RECOVERY_PROTOCOL);
  
  setTimeout(_timeout);

  return 1;
}

void PmmModbusClient::end()
{
  if (_values != NULL) {
    free(_values);

    _values = NULL;
  }

  if (_mb != NULL) {
    modbus_close(_mb);
    modbus_free(_mb);

    _mb = NULL;
  }
}

int PmmModbusClient::coilRead(int address)
{
  return coilRead(_defaultId, address);
}

int PmmModbusClient::coilRead(int id, int address)
{
  uint8_t value;

  modbus_set_slave(_mb, id);
  
  if (modbus_read_bits(_mb, address, 1, &value) < 0) {
    return -1;
  }

  return value;
}

int PmmModbusClient::discreteInputRead(int address)
{
  return discreteInputRead(_defaultId, address);
}

int PmmModbusClient::discreteInputRead(int id, int address)
{
  uint8_t value;

  modbus_set_slave(_mb, id);
  
  if (modbus_read_input_bits(_mb, address, 1, &value) < 0) {
    return -1;
  }

  return value;
}

long PmmModbusClient::holdingRegisterRead(int address)
{
  return holdingRegisterRead(_defaultId, address);
}

long PmmModbusClient::holdingRegisterRead(int id, int address)
{
  uint16_t value;

  modbus_set_slave(_mb, id);
  
  if (modbus_read_registers(_mb, address, 1, &value) < 0) {
    return -1;
  }

  return value;
}

long PmmModbusClient::inputRegisterRead(int address)
{
  return inputRegisterRead(_defaultId, address);
}

long PmmModbusClient::inputRegisterRead(int id, int address)
{
  uint16_t value;

  modbus_set_slave(_mb, id);
  
  if (modbus_read_input_registers(_mb, address, 1, &value) < 0) {
    return -1;
  }

  return value;
}

int PmmModbusClient::coilWrite(int address, uint8_t value)
{
  return coilWrite(_defaultId, address, value);
}

int PmmModbusClient::coilWrite(int id, int address, uint8_t value)
{
  modbus_set_slave(_mb, id);

  if (modbus_write_bit(_mb, address, value) < 0) {
    return 0;
  }

  return 1;
}

int PmmModbusClient::holdingRegisterWrite(int address, uint16_t value)
{
  return holdingRegisterWrite(_defaultId, address, value);
}

int PmmModbusClient::holdingRegisterWrite(int id, int address, uint16_t value)
{
  modbus_set_slave(_mb, id);

  if (modbus_write_register(_mb, address, value) < 0) {
    return 0;
  }

  return 1;
}

int PmmModbusClient::registerMaskWrite(int address, uint16_t andMask, uint16_t orMask)
{
  return registerMaskWrite(_defaultId, address, andMask, orMask);
}

int PmmModbusClient::registerMaskWrite(int id, int address, uint16_t andMask, uint16_t orMask)
{
  modbus_set_slave(_mb, id);

  if (modbus_mask_write_register(_mb, address, andMask, orMask) < 0) {
    return 0;
  }

  return 1;
}

int PmmModbusClient::beginTransmission(int type, int address, int nb)
{
  return beginTransmission(_defaultId, type, address, nb);
}

int PmmModbusClient::beginTransmission(int id, int type, int address, int nb)
{
  if ((type != COILS && type != HOLDING_REGISTERS) || nb < 1) {
    errno = EINVAL;

    return 0;
  }

  int valueSize = (type == COILS) ? sizeof(uint8_t) : sizeof(uint16_t);

  _values = realloc(_values, nb * valueSize);

  if (_values == NULL) {
    errno = ENOMEM;

    return 0;
  }

  memset(_values, 0x00, nb * valueSize);

  _transmissionBegun = true;
  _id = id;
  _type = type;
  _address = address;
  _nb = nb;

  _available = 0;
  _read = 0;
  _availableForWrite = nb;
  _written = 0;

  return 1;
}

int PmmModbusClient::write(unsigned int value)
{
  if (!_transmissionBegun || _availableForWrite <= 0) {
    return 0;
  }

  switch (_type) {
    case COILS:
      ((uint8_t*)_values)[_written++] = value;
      _availableForWrite--;
      return 1;

    case HOLDING_REGISTERS:
      ((uint16_t*)_values)[_written++] = value;
      _availableForWrite--;
      return 1;

    default:
      return 0;
  }

  return 1;
}

int PmmModbusClient::endTransmission()
{
  if (!_transmissionBegun) {
    return 0;
  }

  int result = -1;

  modbus_set_slave(_mb, _id);

  switch (_type) {
    case COILS:
      result = modbus_write_bits(_mb, _address, _nb, (const uint8_t*)_values);
      break;

    case HOLDING_REGISTERS:
      result = modbus_write_registers(_mb, _address, _nb, (const uint16_t*)_values);
      break;

    default:
      return 0;
  }

  _transmissionBegun = false;
  _available = 0;
  _read = 0;
  _availableForWrite = 0;
  _written = 0;

  return (result < 0) ? 0 : 1;
}

int PmmModbusClient::requestFrom(int type, int address, int nb)
{
  return requestFrom(_defaultId, type, address, nb);
}

int PmmModbusClient::requestFrom(int id, int type, int address, int nb)
{
  if ((type != COILS && type != DISCRETE_INPUTS && type != HOLDING_REGISTERS && type != INPUT_REGISTERS) 
      || (nb < 1)) {
    errno = EINVAL;

    return 0;
  }

  int valueSize = (type == COILS || type == DISCRETE_INPUTS) ? sizeof(uint8_t) : sizeof(uint16_t);

  _values = realloc(_values, nb * valueSize);

  if (_values == NULL) {
    errno = ENOMEM;

    return 0;
  }

  int result = -1;

  modbus_set_slave(_mb, id);

  switch (type) {
    case COILS:
      result = modbus_read_bits(_mb, address, nb, (uint8_t*)_values);
      break;

    case DISCRETE_INPUTS:
      result = modbus_read_input_bits(_mb, address, nb, (uint8_t*)_values);
      break;

    case HOLDING_REGISTERS:
      result = modbus_read_registers(_mb, address, nb, (uint16_t*)_values);
      break;

    case INPUT_REGISTERS:
      result = modbus_read_input_registers(_mb, address, nb, (uint16_t*)_values);
      break;

    default:
      break; 
  }

  if (result == -1) {
    return 0;
  }

  _transmissionBegun = false;
  _type = type;
  _available = nb;
  _read = 0;
  _availableForWrite = 0;
  _written = 0;

  return nb;
}

int PmmModbusClient::available()
{
  return _available;
}

long PmmModbusClient::read()
{
  if (_available <= 0) {
    return -1;
  }

  long result = -1;

  switch (_type) {
    case COILS:
    case DISCRETE_INPUTS:
      result = ((uint8_t*)_values)[_read];
      break;

    case HOLDING_REGISTERS:
    case INPUT_REGISTERS:
      result = ((uint16_t*)_values)[_read];
      break;

    default:
      break; 
  }

  if (result != -1) {
    _available--;
    _read++;
  }

  return result;
}

const char* PmmModbusClient::lastError()
{
  if (errno == 0) {
    return NULL;
  }

  return modbus_strerror(errno); 
}

void PmmModbusClient::setTimeout(unsigned long ms)
{
  _timeout = ms;

  if (_mb) {
    modbus_set_response_timeout(_mb, _timeout / 1000, (_timeout % 1000) * 1000);
  }
}
