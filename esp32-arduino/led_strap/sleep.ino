#define WAKEUP_SEC 5

void initDeepSleep()
{
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_MAX, ESP_PD_OPTION_OFF);
  
  esp_deep_sleep_enable_timer_wakeup(WAKEUP_SEC * 1000 * 1000);
}

void enterDeepSleep()
{
  //Serial.println("Entering deep sleep");
  //esp_deep_sleep_start();
}

