#pragma once

#include "queues/umidity.h"
#include "defaults.h"

#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "esp_log.h"

#define TASK_UMIDITYACTUATOR_NAME "umidityactuator"
#define TASK_UMIDITYACTUATOR_STACKSIZE 4096
#define TASK_UMIDITYACTUATOR_OUT_PIN 2
#define TASK_UMIDITYACTUATOR_QUEUE_WAITITME pdMS_TO_TICKS(100)

typedef struct umidityactuator_pvparameters_s
{
    QueueHandle_t hndUmiditySensorQueue;
} umidityactuator_pvparameters_t;

void umid_init()
{
    gpio_set_direction(TASK_UMIDITYACTUATOR_OUT_PIN, GPIO_MODE_OUTPUT);
}

void task_umidityactuator(void *pvParameters)
{
    umid_init();
    QueueHandle_t hndUmiditySensorQueue = ((umidityactuator_pvparameters_t *)pvParameters)->hndUmiditySensorQueue;
    umidityqueue_data_t data = {
        .umidity = 0,
        .temperature = 0};
    if (hndUmiditySensorQueue == NULL)
    {
        ESP_LOGE(TASK_UMIDITYACTUATOR_NAME, "Error receiving queue from pvParameters");
        return;
    }

    ESP_LOGI(TASK_UMIDITYACTUATOR_NAME, "Task started");
    while (1)
    {
        // Receive data from queue
        if (xQueueReceive(hndUmiditySensorQueue, &data, TASK_UMIDITYACTUATOR_QUEUE_WAITITME) != pdTRUE)
        {
            ESP_LOGE(TASK_UMIDITYACTUATOR_NAME, "Error receiving data from queue: is queue empty? AVAILABLE/WAITING: %d/%d", uxQueueSpacesAvailable(hndUmiditySensorQueue), uxQueueMessagesWaiting(hndUmiditySensorQueue));
        }
        else
        {
            ESP_LOGI(TASK_UMIDITYACTUATOR_NAME, "Data received from queue: Umidity: %d%%, Temperature: %d°C", data.umidity / 10, data.temperature / 10);
            if (data.umidity < 300)
            {
                gpio_set_level(TASK_UMIDITYACTUATOR_OUT_PIN, 1);
            }
            else
            {
                gpio_set_level(TASK_UMIDITYACTUATOR_OUT_PIN, 0);
            }
        }
        vTaskDelay(TASK_DEFAULTWAITTIME * 300);
    }
}
