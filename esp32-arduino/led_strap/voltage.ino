#define OHM_1 100
#define OHM_2 300

#define PIN_VOLT_SEND 12
#define PIN_VOLT_RECV 13

float getVoltage()
{
  pinMode(PIN_VOLT_SEND, OUTPUT);
  digitalWrite(PIN_VOLT_SEND, HIGH);
  delay(20);

  int loopCnt = 5;
  float vTotal = 0;
  for (int i = 0; i < loopCnt; i++) {
    vTotal += analogRead(PIN_VOLT_RECV);
  }
  float v = vTotal / loopCnt;
  digitalWrite(PIN_VOLT_SEND, LOW);

  float volt = (1.0273 * v + 596.65) / 1000;
  Serial.println("Voltage: " + (String)volt);
//  Serial.println("v: " + (String)v);
  return volt;
}

