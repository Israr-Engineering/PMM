void setup() {
  // configure all pins  as an output
  for(uint8_t i = 0 ; i < 16 ; i++ )
    pinMode(PMM_DO_Pins[i] ,OUTPUT );
}

void loop() {
  // Loop for turn on all digital outpt pins using --> digitalWrite(pinNumber , pinStats) method
  for(uint8_t i = 0 ; i < 16 ; i++ ){
    digitalWrite(PMM_DO_Pins[i] ,HIGH );
     delay (1000); // delay for 1000 ms
  }
   delay (1000);
  // Loop for turn off all digital outpt pins --> digitalWrite(pinNumber , pinStats) method
  for(uint8_t i = 0 ; i < 16 ; i++ ){
    digitalWrite(PMM_DO_Pins[i] ,LOW );
       delay (1000);
  }
}
