#include <vector>
#include "gatt_server.h"
#include "esp_bt_device.h"

#define SECS_WAIT_FOR_BLE_CONN    60
#define SECS_WAIT_BLE_CONN_FAILED 60 * 15
#define SECS_ONE_YEAR             60 * 60 * 24 * 365

struct BlinkInfo {
  byte blinkPatternId;
  byte brightness;
  byte r;
  byte g;
  byte b;
};

std::vector<BlinkInfo> blinkInfoSet;
GattServer gatt;

bool isDataReceived = false;
int numOfColorsetReceived = 0;

void setup()
{
  initSerial();
  initDeepSleep();
  initLeds();

  /* check if there is enought voltage supplied */
  if ( getVoltage() < 2.2 ) {
    Serial.println("Battery is too low...going into deep sleep");
//    alertAndSleepLowBattery(SECS_ONE_YEAR);
  }

  /* start advertising */
  bleStartAdv();
  Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", ESP_BD_ADDR_HEX(esp_bt_dev_get_address()));

/*
  int elapsedSecs = 0;
  while ( !isDataReceived ) {
    // go into deep-sleep when timeout
    if (elapsedSecs > SECS_WAIT_FOR_BLE_CONN) {
      Serial.println("Failed to connect to the BLE central...going into deep sleep");
      alertAndSleepBleConnFailed(SECS_WAIT_BLE_CONN_FAILED);
    }
    delay(1000);
    elapsedSecs++;
  }

  /* Data received successfully through BLE */
/*
  Serial.println("BLE data received successfully");
  bleStop();
*/
}

void loop()
{
}

