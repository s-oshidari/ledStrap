void initBle()
{
  gatt.begin("ESP32 GattServer");
  gatt.setReadCallback(handleReadCallback);
  gatt.setWriteCallback(handleWriteCallback);
}

void handleReadCallback(esp_ble_gatts_cb_param_t *param)
{
  Serial.printf("GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
}

void handleWriteCallback(esp_ble_gatts_cb_param_t *param)
{
  Serial.printf("GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d\n", param->write.conn_id, param->write.trans_id, param->write.handle);
  Serial.printf("GATT_WRITE_EVT, value len %d, value %08x\n", param->write.len, *(uint32_t *)param->write.value);

  // parse color info
  for (int i = 0; i < param->write.len; i++) {
    Serial.println(param->write.value[i], HEX);
  }
  
  
  //uint32_t value = *(uint32_t *)param->write.value;
  //String valStr = String(*(uint32t *)param->write.value, HEX);
  //Serial.println(valStr);
  
}

