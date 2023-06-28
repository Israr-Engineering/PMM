void setup() {
  // configer All pins as Analog input
  for(uint8_t i = 0 ; i<24 ; i++)
  pinMode(PMM_AI_Pins[i], INPUT);

}

void loop() {
  // read the value from the sensors:
  for(uint8_t i = 0 ; i<24 ; i++)
  {
      uint8_t sensorValue = analogRead(PMM_AI_Pins[i]);

      //print out the value of the sensors:
       String  str = "AI" + String(i+1) + "=" + String(sensorVal) + "   ";
       SerialUSB.print(str);  

      delay(500);
  }

  
}