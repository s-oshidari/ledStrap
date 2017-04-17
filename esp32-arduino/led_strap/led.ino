#include <Adafruit_NeoPixel.h>

#define PIN_LED   14
#define PIN_RGB_C 16
#define PIN_RGB_V 17

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
  setRgbColor(50, 0, 255, 0); delay(mils/2);
  turnOffRgb();               delay(mils/2);
}

void blinkConnected()
{
  byte br = 50;
  byte r =   0;
  byte g =   0;
  byte b = 255;
  
  int blink_on_mils  =  30;
  int blink_off_mils = 150;

  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();
}

void blinkType1(byte br, byte r, byte g, byte b)
{
  /* ●● ○○ ○○ ○○  ○○ ○○ ○○ ○○ */
  int base_mils = 1000;
  int blink_on_mils  =  30;
  int blink_off_mils = 150;
  
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  delay(base_mils - blink_on_mils*2 - blink_off_mils*2);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
}

void blinkType2(byte br, byte r, byte g, byte b)
{
  /* ●○ ○○ ○○ ○○  ○○ ○○ ○○ ○○ */
  int base_mils = 1000;
  int blink_on_mils  =  50;
  
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();
  delay(base_mils - blink_on_mils);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
}

void blinkType3(byte br, byte r, byte g, byte b)
{
  /* ●● ○○ ○○ ○○  ●○ ○○ ○○ ○○ */
  int base_mils = 1000;
  int blink_on_mils  =  30;
  int blink_off_mils = 150;
  
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  delay(base_mils - blink_on_mils*2 - blink_off_mils*2);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);

  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  delay(base_mils - blink_on_mils - blink_off_mils);
  
  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
}

void blinkType4(byte br, byte r, byte g, byte b)
{
  /* ●● ○○ ○○ ○○  ●● ○○ ○○ ○○ */
  int base_mils = 1000;
  int blink_on_mils  =  30;
  int blink_off_mils = 150;
  
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  delay(base_mils - blink_on_mils*2 - blink_off_mils*2);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);

  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();             delay(blink_off_mils);
  delay(base_mils - blink_on_mils*2 - blink_off_mils*2);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
}

void blinkType5(byte br, byte r, byte g, byte b)
{
  /* ●○ ○○ ○○ ○○  ●○ ○○ ○○ ○○ */
  int base_mils = 1000;
  int blink_on_mils  =  50;
  
  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();
  delay(base_mils - blink_on_mils);

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);

  setRgbColor(br, r, g, b); delay(blink_on_mils);
  turnOffRgb();
  delay(base_mils - blink_on_mils);
  
  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
}

void blinkType6(byte br, byte r, byte g, byte b)
{
  /* ～～ ～～ ～～ ～～  ○○ ○○ ○○ ○○ */
  int base_mils = 1000;
  int interval_mils = 50;

  int steps = base_mils / interval_mils * 2;

  for ( int i = 0; i < steps; i++) {
    int _br = br / steps * i;
    setRgbColor(_br, r, g, b);
    delay(interval_mils);
  }
  for ( int i = 0; i < steps; i++) {
    int _br = br / steps * (steps - i);
    setRgbColor(_br, r, g, b);
    delay(interval_mils);
  }
  turnOffRgb();

  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
  delay(base_mils);
}

void blinkType7(byte br, byte r, byte g, byte b)
{
  /* ～～ ～～ ～～ ～～  ～～ ～～ ～～ ～～ */
  int base_mils = 1000;
  int interval_mils = 50;

  int steps = base_mils / interval_mils * 2;

  for ( int i = 0; i < steps; i++) {
    int _br = br / steps * i;
    setRgbColor(_br, r, g, b);
    delay(interval_mils);
  }
  for ( int i = 0; i < steps; i++) {
    int _br = br / steps * (steps - i);
    setRgbColor(_br, r, g, b);
    delay(interval_mils);
  }
  for ( int i = 0; i < steps; i++) {
    int _br = br / steps * i;
    setRgbColor(_br, r, g, b);
    delay(interval_mils);
  }
  for ( int i = 0; i < steps; i++) {
    int _br = br / steps * (steps - i);
    setRgbColor(_br, r, g, b);
    delay(interval_mils);
  }
}

