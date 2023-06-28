void setup() {
  
  
  // configer Analog input pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  pinMode(PMM_AI_Pins[i], INPUT);
  
  // configer Analog output pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  pinMode(PMM_AO_Pins[i], OUTPUT);

  // configer Digital input pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  pinMode(PMM_DI_Pins[i], INPUT_PULLUP);

  // configer Digital output pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  pinMode(PMM_DO_Pins[i], OUTPUT);
  


}

void loop() {
  // write values for Alnalog output pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  {
       analogWrite(PMM_AO_Pins[i] , i);
      delay(500);
  }

  // read values from Alnalog input pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  {
      uint8_t sensorValue = analogRead(PMM_AI_Pins[i]);

      //print out the value of the sensors:
       String  str = "AI" + String(i+1) + "=" + String(sensorVal) + "   ";
       SerialUSB.print(str);  

      delay(500);
  }

    // write values for Digital output pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  {
       digitalWrite(PMM_DO_Pins[i] , HIGH);
      delay(500);
  }

  // read values from Digital input pins:
  for(uint8_t i = 0 ; i<2 ; i++)
  {
       bool sensorVal = digitalRead(PMM_DI_Pins[i]);

      sensorVal =  !sensorVal;

      //print out the value of the pushbutton
       String  str = "DI" + String(i+1) + "=" + String(sensorVal) + "   ";
       SerialUSB.print(str);    
  }



  
}