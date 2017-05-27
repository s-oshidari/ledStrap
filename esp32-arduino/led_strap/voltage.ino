#define PIN_VOLT_RECV A0

float getVoltage()
{
  int loopCnt = 20;
  float vTotal = 0;
  for (int i = 0; i < loopCnt; i++) {
    vTotal += analogRead(PIN_VOLT_RECV);
    delay(5);
  }
  float v = vTotal / loopCnt;

  float volt = (0.7997 * v + 263.76) / 1000;
  Serial.print("v: " + (String)v + "    ");
  Serial.println("Voltage: " + (String)volt);
  return volt;
}

