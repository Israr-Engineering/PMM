#include <Schedule.h>

void setup() {

  SerialUSB.begin(9600);
  Ethernet.begin();
  Wire.begin();

  Scheduler.startLoop(PMMConfiguration);
  Scheduler.startLoop(PMMProcess);
}
 
void loop() {
 
}

void PMMConfiguration() {
  
}

void PMMProcess() {

  // We must call 'yield' at a regular basis to pass

  // control to other tasks.

  yield();
}