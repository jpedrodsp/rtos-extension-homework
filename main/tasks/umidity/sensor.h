#pragma once

#include "defaults.h"

#include "freertos/task.h"
#include "freertos/queue.h"

#include "dht.h"

#include "esp_log.h"

#define TASK_UMIDITYSENSOR_NAME "umiditysensor"
#define TASK_UMIDITYSENSOR_STACKSIZE 2048
#define TASK_UMIDITYSENSOR_DHT_IN_PIN 23
#define TASK_UMIDITYSENSOR_DHT_TYPE DHT_TYPE_AM2301 // This type is used for DHT22

typedef struct umiditysensor_data_s
{
    int16_t umidity;
    int16_t temperature;
} umiditysensor_data_t;

typedef struct umiditysensor_pvparameters_s
{
    QueueHandle_t hndUmiditySensorQueue;
} umiditysensor_pvparameters_t;

void task_umiditysensor(void *pvParameters)
{
    // Receive queue from pvParameters
    QueueHandle_t hndUmiditySensorQueue = ((umiditysensor_pvparameters_t *)pvParameters)->hndUmiditySensorQueue;
    esp_err_t err;
    int16_t actual_umidity;
    int16_t actual_temperature;
    ESP_LOGI(TASK_UMIDITYSENSOR_NAME, "Task started");
    while (1)
    {
        err = dht_read_data(
            TASK_UMIDITYSENSOR_DHT_TYPE,
            TASK_UMIDITYSENSOR_DHT_IN_PIN,
            &actual_umidity,
            &actual_temperature);
        if (err != ESP_OK)
        {
            // TODO: Implement error handling
            ESP_LOGE(TASK_UMIDITYSENSOR_NAME, "Error reading data from DHT22");
        }
        else
        {
            // Send data to queue
            umiditysensor_data_t data = {
                .umidity = actual_umidity,
                .temperature = actual_temperature};
            if (xQueueSend(hndUmiditySensorQueue, &data, pdMS_TO_TICKS(100)) != pdTRUE)
            {
                ESP_LOGE(TASK_UMIDITYSENSOR_NAME, "Error sending data to queue");
                ESP_LOGE(TASK_UMIDITYSENSOR_NAME, "Queu Stack %d/%d", uxQueueSpacesAvailable(hndUmiditySensorQueue), uxQueueMessagesWaiting(hndUmiditySensorQueue));
            }
            else
            {
                ESP_LOGI(TASK_UMIDITYSENSOR_NAME, "Data sent to queue: Umidity: %d%%, Temperature: %d°C", data.umidity / 10, data.temperature / 10);
            }
        }
        vTaskDelay(TASK_DEFAULTWAITTIME * 100);
    }
}