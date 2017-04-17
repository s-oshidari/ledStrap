void bleStartAdv()
{
  gatt.begin("OSHIRASE Strap");
  gatt.setConnectCallback(handleConnectCallback);
  gatt.setReadCallback(handleReadCallback);
  gatt.setWriteCallback(handleWriteCallback);
}

void bleStop()
{
  if (btStarted()) {
    btStop();
  }
}

void handleConnectCallback(esp_ble_gatts_cb_param_t *param)
{
  Serial.printf("SERVICE_START_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:, is_conn %d\n",
           param->connect.conn_id,
           param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
           param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5],
           param->connect.is_connected);

  blinkConnected();
}

void handleReadCallback(esp_ble_gatts_cb_param_t *param)
{
  Serial.printf("GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
  // nothing to do here...
}

void handleWriteCallback(esp_ble_gatts_cb_param_t *param)
{
  Serial.printf("GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d\n", param->write.conn_id, param->write.trans_id, param->write.handle);
  Serial.printf("GATT_WRITE_EVT, value len %d, value %08x\n", param->write.len, *(uint32_t *)param->write.value);

  if ( isDataReceived ) {
    Serial.println("Colorset data already received");
    return;
  }
  
  // parse color info
  uint16_t len = param->write.len;
  uint8_t *val = param->write.value;

  for (int i = 0; i < len; i++) {
    Serial.print(val[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  uint8_t d_ver = val[0];
  switch (d_ver) {
    case 1:
      handleColorData_v1(len, val);
      break;
    default:
      Serial.println("Undefined data version: " + (String)d_ver );
      alertAndSleepError(SECS_ONE_YEAR);
  }
}

void checkDataLength(uint16_t len_test, uint16_t len_correct)
{
  if (len_test != len_correct) {
    Serial.println("Incomplete data length: " + (String)len_test + " (len must be " + (String)len_correct + ")");
    alertAndSleepError(SECS_ONE_YEAR);
  }
}

void handleColorData_v1(uint16_t len, uint8_t *val)
{
  checkDataLength(len, 9);

  byte d_isHeader          = val[1];
  byte d_numOfColorset     = val[2];
  byte d_minsTillNextCheck = val[3];
  byte d_blinkPatternId    = val[4];
  byte d_brightness        = val[5];
  byte d_colorRed          = val[6];
  byte d_colorGreen        = val[7];
  byte d_colorBlue         = val[8];


  if ( d_numOfColorset == 0 ) {
    Serial.println("Received data contains no colorset");
    alertAndSleepBleNoData(d_minsTillNextCheck * 60);
  }

  if ( d_isHeader ) {
    Serial.println("header received");
    numOfColorsetReceived = 0;
    blinkInfoSet.clear();
    blinkInfoSet.shrink_to_fit();
    return;
  }

  /* data received */

  Serial.println("adding colorset");
  blinkInfoSet.push_back({ d_blinkPatternId, d_brightness, d_colorRed, d_colorGreen, d_colorBlue });
  numOfColorsetReceived++;

  if ( numOfColorsetReceived < d_numOfColorset ) {
    return;
  }

  /* final dataset received */
  
  Serial.println("final data received");
  isDataReceived = true;
  numOfColorsetReceived = 0;

  int currentSecs = (millis() / 1000);
  int secsToEnd = currentSecs + (d_minsTillNextCheck * 60);
  
  while (currentSecs < secsToEnd) {
    Serial.print("Current: "); Serial.print(currentSecs);
    Serial.print("  ToEnd: "); Serial.println(secsToEnd);
    
    for ( auto blinkInfo = blinkInfoSet.begin(); blinkInfo != blinkInfoSet.end(); ++blinkInfo) {
      switch ((*blinkInfo).blinkPatternId) {
        case 1:
          blinkType1( (*blinkInfo).brightness, (*blinkInfo).r, (*blinkInfo).g, (*blinkInfo).b );
          break;
        case 2:
          blinkType2( (*blinkInfo).brightness, (*blinkInfo).r, (*blinkInfo).g, (*blinkInfo).b );
          break;
        case 3:
          blinkType3( (*blinkInfo).brightness, (*blinkInfo).r, (*blinkInfo).g, (*blinkInfo).b );
          break;
        case 4:
          blinkType4( (*blinkInfo).brightness, (*blinkInfo).r, (*blinkInfo).g, (*blinkInfo).b );
          break;
        case 5:
          blinkType5( (*blinkInfo).brightness, (*blinkInfo).r, (*blinkInfo).g, (*blinkInfo).b );
          break;
        case 6:
          blinkType6( (*blinkInfo).brightness, (*blinkInfo).r, (*blinkInfo).g, (*blinkInfo).b );
          break;
        case 7:
          blinkType7( (*blinkInfo).brightness, (*blinkInfo).r, (*blinkInfo).g, (*blinkInfo).b );
          break;
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

