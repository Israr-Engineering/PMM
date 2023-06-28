void setup() {
  // configure all Digital output pins as an output
  for (uint8_t i = 0; i < 6; i++)
    pinMode(PMM_DO_Pins[i], OUTPUT);

  // configure all Digital input pins as an input
  for (uint8_t i = 0; i < 12; i++)
    pinMode(PMM_DI_Pins[i], INPUT_PULLUP);

  // Loop for turn off all digital outpt pins --> digitalWrite(pinNumber , pinStats) method
  for (uint8_t i = 0; i < 6; i++) {
    digitalWrite(PMM_DO_Pins[i], LOW);
  }
}

void loop() {
  // Loop for turn on all digital outpt pins --> digitalWrite(pinNumber , pinStats) method
  for (uint8_t i = 0; i < 6; i++) {
    digitalWrite(PMM_DO_Pins[i], HIGH);
    delay(1000);
  }

  //save the digital inputs values into a variable and print it's status
  for (uint8_t i = 0; i < 12; i++) {
    bool sensorVal = digitalRead(PMM_DI_Pins[i]);

    sensorVal = !sensorVal;

    //print out the value of the pushbutton
    String str = "DI" + String(i + 1) + "=" + String(sensorVal) + "   ";
    SerialUSB.print(str);
  }
  SerialUSB.println("");
  delay(1000);
}