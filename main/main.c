#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TASK_DEFAULTWAITTIME pdMS_TO_TICKS(10)

void task_umiditysensor(void *pvParameters)
{
    ESP_LOGI("task_umiditysensor", "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}

void task_display(void *pvParameters)
{
    ESP_LOGI("task_display", "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}

void task_umidityactuator(void *pvParameters)
{
    ESP_LOGI("task_umidityactuator", "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}

void init_hw(void)
{

}

void app_main(void)
{
    init_hw();
    xTaskCreate(task_umiditysensor, "umiditysensor", 2048, NULL, 1, NULL);
    xTaskCreate(task_display, "display", 2048, NULL, 1, NULL);
    xTaskCreate(task_umidityactuator, "umidityactuator", 2048, NULL, 1, NULL);
}