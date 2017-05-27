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

void handleReadCallback(esp_ble_gatts_cb_param_t *param, esp_gatt_value_t *attr_value)
{
  Serial.printf("GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);

  uint32_t n = (uint32_t)(voltage * 100);
  attr_value->len = 4;
  attr_value->value[0] = (n >> 24) & 0xFF;
  attr_value->value[1] = (n >> 16) & 0xFF;
  attr_value->value[2] = (n >>  8) & 0xFF;
  attr_value->value[3] = (n >>  0) & 0xFF;
}

void handleWriteCallback(esp_ble_gatts_cb_param_t *param)
{
  Serial.printf("GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d\n", param->write.conn_id, param->write.trans_id, param->write.handle);
  Serial.printf("GATT_WRITE_EVT, value len %d, value %08x\n", param->write.len, *(uint32_t *)param->write.value);

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

  if (isBlinking) {
    vTaskDelete(taskBlink);
  }
  xTaskCreate(&blinkByType, "blinkByType", 2048, (void *)d_minsTillNextCheck, 1, &taskBlink);
}

