void setup() {
SerialUSB.begin(9600);

  //configure all pins  as an input and enable the internal pull-up resistor
  for(uint8_t i=0 ; i < 12 ; i++)
      pinMode(PMM_DI_Pins[i], INPUT_PULLUP);
  
}

void loop() {
  //save the digital inputs values into a variable and print it's status 
   for(uint8_t i=0 ; i < 12 ; i++){
      bool sensorVal = digitalRead(PMM_DI_Pins[i]);

      sensorVal =  !sensorVal;

      //print out the value of the pushbutton
       String  str = "DI" + String(i+1) + "=" + String(sensorVal) + "   ";
       SerialUSB.print(str);    
  }  
 SerialUSB.println("");
 delay(1000);
}
