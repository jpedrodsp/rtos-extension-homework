#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TASK_DEFAULTWAITTIME pdMS_TO_TICKS(10)

void task_getumidityvalues(void *pvParameters)
{
    ESP_LOGI("task_getumidityvalues", "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}

void task_updatedisplay(void *pvParameters)
{
    ESP_LOGI("task_updatedisplay", "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}

void task_controlhumidity(void *pvParameters)
{
    ESP_LOGI("task_controlhumidity", "Task started");
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
    xTaskCreate(task_getumidityvalues, "task_getumidityvalues", 2048, NULL, 1, NULL);
    xTaskCreate(task_updatedisplay, "task_updatedisplay", 2048, NULL, 1, NULL);
    xTaskCreate(task_controlhumidity, "task_controlhumidity", 2048, NULL, 1, NULL);
}