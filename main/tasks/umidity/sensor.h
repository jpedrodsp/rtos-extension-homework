#pragma once

#include "queues/umidity.h"
#include "defaults.h"

#include "freertos/task.h"
#include "freertos/queue.h"

#include "dht.h"

#include "esp_log.h"

#define TASK_UMIDITYSENSOR_NAME "umiditysensor"
#define TASK_UMIDITYSENSOR_STACKSIZE 4096
#define TASK_UMIDITYSENSOR_DHT_IN_PIN 23
#define TASK_UMIDITYSENSOR_DHT_TYPE DHT_TYPE_AM2301 // This type is used for DHT22
#define TASK_UMIDITYSENSOR_QUEUE_WAITITME 0

typedef struct umiditysensor_pvparameters_s
{
    QueueHandle_t hndUmiditySensorQueue;
} umiditysensor_pvparameters_t;

void task_umiditysensor(void *pvParameters)
{
    // Receive queue from pvParameters
    esp_err_t err = ESP_OK;
    QueueHandle_t hndUmiditySensorQueue = ((umiditysensor_pvparameters_t *)pvParameters)->hndUmiditySensorQueue;
    umidityqueue_data_t data = {
        .umidity = 0,
        .temperature = 0};
    if (hndUmiditySensorQueue == NULL)
    {
        ESP_LOGE(TASK_UMIDITYSENSOR_NAME, "Error receiving queue from pvParameters");
        return;
    }

    ESP_LOGI(TASK_UMIDITYSENSOR_NAME, "Task started");
    while (1)
    {
        err = dht_read_data(
            TASK_UMIDITYSENSOR_DHT_TYPE,
            TASK_UMIDITYSENSOR_DHT_IN_PIN,
            &data.umidity,
            &data.temperature);
        if (err != ESP_OK)
        {
            // TODO: Implement error handling
            ESP_LOGE(TASK_UMIDITYSENSOR_NAME, "Error reading data from DHT22");
        }
        else
        {
            // Send data to queue
            if (xQueueSend(hndUmiditySensorQueue, &data, TASK_UMIDITYSENSOR_QUEUE_WAITITME) != pdTRUE)
            {
                ESP_LOGE(TASK_UMIDITYSENSOR_NAME, "Error sending data to queue: is queue full? AVAILABLE/WAITING: %d/%d", uxQueueSpacesAvailable(hndUmiditySensorQueue), uxQueueMessagesWaiting(hndUmiditySensorQueue));
            }
            else
            {
                ESP_LOGI(TASK_UMIDITYSENSOR_NAME, "Data sent to queue: Umidity: %d%%, Temperature: %d°C", data.umidity / 10, data.temperature / 10);
            }
        }
        vTaskDelay(TASK_DEFAULTWAITTIME * 100);
    }
}