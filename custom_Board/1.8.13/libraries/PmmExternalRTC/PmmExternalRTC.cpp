#include "PmmExternalRTC.h"
#include "PmmDS3231.h"

#include <string>
using namespace std;

PmmRTClib PMMDS3231;
PmmDS3231 RTCSetTime;

bool PMMInitializeExternalRTC();
void PMMSetRTCUNIXTime(uint32_t unixTime);
DateTime PMMGetRTCNOW();
uint32_t PMMGetRTCUNIXTime();
uint8_t PMMReturnMonthNumber();
uint8_t PMMReturnDayNumber();
int16_t PMMReturnDayOfYear();
int16_t PMMReturnCurrentHour();
int16_t PMMReturnCurrentMinute();
bool PMMRTCCheck();
string PMMRTCStringTime();

bool PMMInitializeExternalRTC()
{
    bool RTCFound = false;
    RTCFound = PMMRTCCheck();
    if (RTCFound)
    {
        RTCFound = true;
    }
    return RTCFound;
}

bool PMMRTCCheck()
{
    Wire.beginTransmission(0x68);
    bool RTCFound = Wire.endTransmission() == 0;
    return RTCFound;
}

DateTime PMMGetRTCNOW()
{
    DateTime now = PMMDS3231.now();
    return now;
}

uint32_t PMMGetRTCUNIXTime()
{
    DateTime now = PMMDS3231.now();
    return now.unixtime();
}

void PMMSetRTCUNIXTime(uint32_t unixTime)
{
    RTCSetTime.setEpoch(unixTime);
}

uint8_t PMMReturnMonthNumber()
{
    DateTime now = PMMDS3231.now();
    return now.month();
}

uint8_t PMMReturnDayNumber()
{
    DateTime now = PMMDS3231.now();
    return now.day();
}

int16_t PMMReturnDayOfYear()
{
    DateTime now = PMMDS3231.now();
    byte monthIndex = now.month();
    byte dayNumber = now.day();
    const uint8_t daysInMonth[] PROGMEM = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    int16_t numberOfDays = 0;
    for (uint8_t i = 0; i < (monthIndex - 1); i++)
        numberOfDays += daysInMonth[i];
    numberOfDays += dayNumber;
    return numberOfDays;
}

int16_t PMMReturnCurrentHour()
{
    DateTime now = PMMDS3231.now();
    return now.hour();
}

int16_t PMMReturnCurrentMinute()
{
    DateTime now = PMMDS3231.now();
    return now.hour() * 60 + now.minute();
}

string PMMRTCStringTime()
{
    DateTime now = PMMDS3231.now();

    string returnDate = std::to_string(now.year()) + "-" +
                        std::to_string(now.month()) + "-" +
                        std::to_string(now.day()) + " " +
                        std::to_string(now.hour()) + ":" +
                        std::to_string(now.minute()) + ":" +
                        std::to_string(now.second());
    return returnDate;
}
