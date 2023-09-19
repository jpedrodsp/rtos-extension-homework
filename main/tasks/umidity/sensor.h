#pragma once

#include "defaults.h"

#include "freertos/task.h"

#include "dht.h"

#include "esp_log.h"

#define TASK_UMIDITYSENSOR_NAME "umiditysensor"
#define TASK_UMIDITYSENSOR_STACKSIZE 2048
#define TASK_UMIDITYSENSOR_DHT_IN_PIN 23
#define TASK_UMIDITYSENSOR_DHT_TYPE DHT_TYPE_AM2301 // This type is used for DHT22

void task_umiditysensor(void *pvParameters)
{
    esp_err_t err;
    int16_t actual_umidity;
    int16_t actual_temperature;
    ESP_LOGI(TASK_UMIDITYSENSOR_NAME, "Task started");
    while(1)
    {
        err = dht_read_data(
            TASK_UMIDITYSENSOR_DHT_TYPE,
            TASK_UMIDITYSENSOR_DHT_IN_PIN,
            &actual_umidity,
            &actual_temperature
        );
        if (err != ESP_OK) {
            // TODO: Implement error handling
            ESP_LOGE(TASK_UMIDITYSENSOR_NAME, "Error reading data from DHT22");
        } else {
            ESP_LOGW(TASK_UMIDITYSENSOR_NAME, "Umidity: %d%%, Temperature: %d°C", actual_umidity / 10, actual_temperature / 10);
            // TODO: Implement data handling
            //ESP_LOGW(TASK_UMIDITYSENSOR_NAME, "Data handling not implemented");
        }
        vTaskDelay(TASK_DEFAULTWAITTIME * 100);
    }
}