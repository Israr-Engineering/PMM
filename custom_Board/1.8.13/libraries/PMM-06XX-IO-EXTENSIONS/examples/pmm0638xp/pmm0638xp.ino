void setup() {
  // configer All pins as Analog output:
  for(uint8_t i = 0 ; i<12 ; i++)
  pinMode(PMM_AO_Pins[i], OUTPUT);

   // configer All pins as Analog input
  for(uint8_t i = 0 ; i<12 ; i++)
  pinMode(PMM_AI_Pins[i], INPUT);

}

void loop() {
  // write values for Alnalog output pins:
  for(uint8_t i = 0 ; i<12 ; i++)
  {
       analogWrite(PMM_AI_Pins[i] , i);
      delay(500);
  }

   // read the value from the sensors:
  for(uint8_t i = 0 ; i<12 ; i++)
  {
      uint8_t sensorValue = analogRead(PMM_AI_Pins[i]);

      //print out the value of the sensors:
       String  str = "AI" + String(i+1) + "=" + String(sensorVal) + "   ";
       SerialUSB.print(str);  

      delay(500);
  }

}

