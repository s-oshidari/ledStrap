void initDeepSleep()
{
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_MAX, ESP_PD_OPTION_OFF);
}

void enterDeepSleep(uint32_t secs)
{
  esp_deep_sleep_enable_timer_wakeup(secs * 1000 * 1000);

  Serial.println("Entering deep sleep for " + (String)secs + " seconds");
  esp_deep_sleep_start();
}

