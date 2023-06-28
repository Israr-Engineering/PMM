void setup()
{
  // configure all pins  as an output
  for (uint8_t i = 0; i < 8; i++)
    pinMode(PMM_DO_Pins[i], OUTPUT);

  // Loop for turn off all digital outpt pins --> digitalWrite(pinNumber , pinStats) method
  for (uint8_t i = 0; i < 8; i++)
  {
    digitalWrite(PMM_DO_Pins[i], LOW);
  }
}

void loop()
{
  // Loop for turn off all digital outpt pins --> digitalWrite(pinNumber , pinStats) method
  for (uint8_t i = 0; i < 8; i++)
    digitalWrite(PMM_DO_Pins[i], HIGH);
}
