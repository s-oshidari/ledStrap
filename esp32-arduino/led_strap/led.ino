#include <Adafruit_NeoPixel.h>

#define PIN_LED   14
#define PIN_RGB_C 23
#define PIN_RGB_V 22

Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(1, PIN_RGB_C, NEO_RGB + NEO_KHZ800);

void initLeds()
{
  // White
  pinMode(PIN_LED, OUTPUT);

  // RGB
  pinMode(PIN_RGB_V, OUTPUT);
  digitalWrite(PIN_RGB_V, HIGH);
  RGBLED.begin();
  turnOffRgb();
  setRgbColor(0, 255, 255, 255);
}

void turnOffRgb() {
  setRgbColor(0, 255, 255, 255);
}

void setRgbColor(int brightness, int r, int g, int b) // 0~255
{
  RGBLED.setBrightness(brightness);
  RGBLED.setPixelColor(0, r, g, b);
  RGBLED.show();
}

void blinkRgb(int mils)
{
  setRgbColor(50, 0, 255, 0); delayTask(mils/2);
  turnOffRgb();               delayTask(mils/2);
}

void blinkConnected()
{
  byte br = 50;
  byte r =   0;
  byte g =   0;
  byte b = 255;
  
  int mils_on  =  30;
  int mils_off = 150;

  setRgbColor(br, r, g, b); delayTask(mils_on);
  turnOffRgb();             delayTask(mils_off);
  setRgbColor(br, r, g, b); delayTask(mils_on);
  turnOffRgb();
}

void blinkByType(void *p)
{
  isBlinking = true;
  int minsTillNextCheck = (int)p;
  int currentSecs = (millis() / 1000);
  int secsToEnd = currentSecs + (minsTillNextCheck * 60);

  while (currentSecs < secsToEnd) {
    
    Serial.print("Current: "); Serial.print(currentSecs);
    Serial.print("  ToEnd: "); Serial.println(secsToEnd);

    for ( auto blinkInfo = blinkInfoSet.begin(); blinkInfo != blinkInfoSet.end(); ++blinkInfo) {
      int br = (*blinkInfo).brightness;
      int r = (*blinkInfo).r;
      int g = (*blinkInfo).g;
      int b = (*blinkInfo).b;
      
      switch ((*blinkInfo).blinkPatternId) {
        case 1: blinkType1(br, r, g, b); break; /* ●○ ○○ ○○ ○○  ●○ ○○ ○○ ○○ */
        case 2: blinkType2(br, r, g, b); break; /* ●● ○○ ○○ ○○  ●● ○○ ○○ ○○ */
        case 3: blinkType3(br, r, g, b); break; /* ●○ ○○ ●○ ○○  ●○ ○○ ●○ ○○ */
        case 4: blinkType4(br, r, g, b); break; /* ●● ○○ ●● ○○  ●● ○○ ●● ○○ */
        case 5: blinkType5(br, r, g, b); break; /* ●○ ●○ ●○ ●○  ●○ ●○ ●○ ●○ */
        case 6: blinkType6(br, r, g, b); break; /* ～～ ～～ ～～ ～～  ○○ ○○ ○○ ○○ */
        case 7: blinkType7(br, r, g, b); break; /* ～～ ～～ ～～ ～～  ～～ ～～ ～～ ～～ */
        default:
          Serial.println("Undefined blink type: " + (String)(*blinkInfo).blinkPatternId );
          alertAndSleepError(SECS_ONE_YEAR);
      }
    }
    currentSecs = (millis() / 1000);
  }

  Serial.println("Blink iteration completed...will check again in no time");
  enterDeepSleep(0);
}

/* -------- CUSTOM BLINK TYPES -------- */

void blinkType1(byte br, byte r, byte g, byte b)
{
  /* ●○ ○○ ○○ ○○  ●○ ○○ ○○ ○○ */
  int mils_base = 1000;
  int mils_on   =  100;

  setRgbColor(br, r, g, b);
  delayTask(mils_on);
  turnOffRgb();
  delayTask(mils_base * 4 - mils_on);
}

void blinkType2(byte br, byte r, byte g, byte b)
{
  /* ●● ○○ ○○ ○○  ●● ○○ ○○ ○○ */
  int mils_base = 1000;
  int mils_on   =   50;
  int mils_off  =  150;
  
  for (int j = 0; j < 2; j++) {
    setRgbColor(br, r, g, b);
    delayTask(mils_on);
    turnOffRgb();
    delayTask(mils_off);
  }
  delayTask(mils_base * 4 - mils_on * 2 - mils_off * 2);
}

void blinkType3(byte br, byte r, byte g, byte b)
{
  /* ●○ ○○ ●○ ○○  ●○ ○○ ●○ ○○ */
  int mils_base = 1000;
  int mils_on   =  100;

  for (int i = 0; i < 2; i++) {
    setRgbColor(br, r, g, b);
    delayTask(mils_on);
    turnOffRgb();
    delayTask(mils_base * 2 - mils_on);
  }
}

void blinkType4(byte br, byte r, byte g, byte b)
{
  /* ●● ○○ ●● ○○  ●● ○○ ●● ○○ */
  int mils_base = 1000;
  int mils_on   =   50;
  int mils_off  =  100;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      setRgbColor(br, r, g, b);
      delayTask(mils_on);
      turnOffRgb();
      delayTask(mils_off);
    }
    delayTask(mils_base * 2 - mils_on * 2 - mils_off * 2);
  }
}

void blinkType5(byte br, byte r, byte g, byte b)
{
  /* ●○ ●○ ●○ ●○  ●○ ●○ ●○ ●○ */
  int mils_base = 1000;
  int mils_on   =   50;

  for (int i = 0; i < 4; i++) {
    setRgbColor(br, r, g, b);
    delayTask(mils_on);
    turnOffRgb();
    delayTask(mils_base - mils_on);
  }
}

void blinkType6(byte br, byte r, byte g, byte b)
{
  /* ～～ ～～ ～～ ～～  ○○ ○○ ○○ ○○ */
  int mils_base     = 1000;
  int mils_interval =   50;

  int steps = mils_base * 2 / mils_interval;

  for (int i = 0; i < steps; i++) {
    int _br = br / steps * i;
    setRgbColor(_br, r, g, b);
    delayTask(mils_interval);
  }
  for (int i = 0; i < steps; i++) {
    int _br = br / steps * (steps - i);
    setRgbColor(_br, r, g, b);
    delayTask(mils_interval);
  }
  turnOffRgb();

  delayTask(mils_base * 4);
}

void blinkType7(byte br, byte r, byte g, byte b)
{
  /* ～～ ～～ ～～ ～～  ～～ ～～ ～～ ～～ */
  int mils_base     = 1000;
  int mils_interval =   50;
  int mils_off      =  600;

  int steps = (mils_base * 2 - mils_off / 2) / mils_interval;

  for (int i = 0; i < steps; i++) {
    int _br = br / steps * i;
    setRgbColor(_br, r, g, b);
    delayTask(mils_interval);
  }
  for (int i = 0; i < steps; i++) {
    int _br = br / steps * (steps - i);
    setRgbColor(_br, r, g, b);
    delayTask(mils_interval);
  }
  turnOffRgb();
  delayTask(mils_off);
}

