#define OHM_1 100
#define OHM_2 300

#define PIN_VOLT_SEND 25
#define PIN_VOLT_RECV 36

float getVoltage()
{
  pinMode(PIN_VOLT_SEND, OUTPUT);
  digitalWrite(PIN_VOLT_SEND, HIGH);
  delay(20);
  float v = analogRead(PIN_VOLT_RECV);
  digitalWrite(PIN_VOLT_SEND, LOW);

  float volt = 0.001 * v - 1.0415;
  return volt;
}

