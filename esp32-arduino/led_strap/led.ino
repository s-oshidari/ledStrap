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
  setRgbColor(0, 0, 0, 0);
}

void blinkLed()
{
  digitalWrite(PIN_LED, HIGH);
  delay(250);
  digitalWrite(PIN_LED, LOW);
  delay(250);
}

void setRgbColor(int brightness, int r, int g, int b) // 0~255
{
  RGBLED.setBrightness(brightness);
  RGBLED.setPixelColor(0, r, g, b);
  RGBLED.show();
}

void testAlert()
{
  int brightness = 100;
  int r = 0;
  int g = 0;
  int b = 0;
  
  setRgbColor(brightness, r, g, b);
}

