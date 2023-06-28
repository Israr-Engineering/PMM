void setup() {
  // configer All pins as Analog output:
  for(uint8_t i = 0 ; i<8 ; i++)
  pinMode(PMM_AO_Pins[i], OUTPUT);

}

void loop() {
  // write values for Alnalog output pins:
  for(uint8_t i = 0 ; i<8 ; i++)
  {
       analogWrite(PMM_AO_Pins[i] , i);
      delay(500);
  }

  
}