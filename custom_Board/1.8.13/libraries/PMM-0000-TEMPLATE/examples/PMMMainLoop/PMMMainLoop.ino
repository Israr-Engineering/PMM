#include <ProjectDef.h>

void setup() {

  Scheduler.startLoop(PMMConfiguration);
  Scheduler.startLoop(PMMCommunication);
}

void loop() {
 
}

void PMMConfiguration() {
}

void PMMCommunication() {

  // We must call 'yield' at a regular basis to pass

  // control to other tasks.

  yield();
}