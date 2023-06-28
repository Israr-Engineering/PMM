#include <ProjectDef.h>
#include <PMMGlobalFunctions.h>
#include <PMMCommands.h>


byte mac[] = { 0x84, 0x42, 0x8B, 0xBA, 0xB2, 0x31 };
IPAddress ip(192, 168, 1, 10);

void setup() {

  SerialUSB.begin(9600);
  PMMInitializeEthernet(ip,mac);
  PMMInitializeEEPROM();  // Initialize EEPROM
  InitializeWire();
  
  Scheduler.startLoop(PMMConfiguration);
  Scheduler.startLoop(PMMCommunication);
}

void loop() {
 
}

void PMMConfiguration() {
  PMMReadCommands();
}

void PMMCommunication() {

  // We must call 'yield' at a regular basis to pass

  // control to other tasks.

  yield();
}