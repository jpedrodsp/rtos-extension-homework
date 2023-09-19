#pragma once

#include "queues/umidity.h"
#include "defaults.h"

#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"

#define TASK_UMIDITYACTUATOR_NAME "umidityactuator"
#define TASK_UMIDITYACTUATOR_STACKSIZE 2048
#define TASK_UMIDITYACTUATOR_OUT_PIN 24

typedef struct umidityactuator_pvparameters_s
{
    QueueHandle_t hndUmiditySensorQueue;
} umidityactuator_pvparameters_t;

void task_umidityactuator(void *pvParameters)
{
    QueueHandle_t hndUmiditySensorQueue = ((umidityactuator_pvparameters_t *)pvParameters)->hndUmiditySensorQueue;
    umidityqueue_data_t data;

    ESP_LOGI(TASK_UMIDITYACTUATOR_NAME, "Task started");
    while(1)
    {
        if (xQueueReceive(hndUmiditySensorQueue, &data, TASK_DEFAULTWAITTIME * 100) != pdTRUE)
        {
            ESP_LOGE(TASK_UMIDITYACTUATOR_NAME, "Error receiving data from queue: is queue empty? AVAILABLE/WAITING: %d/%d", uxQueueSpacesAvailable(hndUmiditySensorQueue), uxQueueMessagesWaiting(hndUmiditySensorQueue));
        }
        else
        {
            ESP_LOGI(TASK_UMIDITYACTUATOR_NAME, "Data received from queue: Umidity: %d%%, Temperature: %d°C", data.umidity / 10, data.temperature / 10);
        }
        vTaskDelay(TASK_DEFAULTWAITTIME * 100);
    }
}