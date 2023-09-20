#pragma once

#include "defaults.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TASK_MONITOR_NAME "monitor"
#define TASK_MONITOR_STACKSIZE 2048

typedef struct monitor_pvparameters_s
{
    TaskHandle_t hndUmiditySensor;
    TaskHandle_t hndUmidityActuator;
    TaskHandle_t hndDisplay;
    TaskHandle_t hndMonitor;
} monitor_pvparameters_t;

void task_monitor(void *pvParameters)
{
    monitor_pvparameters_t data = *((monitor_pvparameters_t *)pvParameters);
    ESP_LOGI(TASK_MONITOR_NAME, "Task started");
    while(1)
    {
        // Show information of tasks
        if (data.hndUmiditySensor != NULL)
        {
            TaskStatus_t statusUmidityActuator;
            vTaskGetInfo(data.hndUmidityActuator, &statusUmidityActuator, pdTRUE, eInvalid);
            if (data.hndUmidityActuator != NULL)
            {
                ESP_LOGI(TASK_MONITOR_NAME, "Task %s - STACK_LEFT %d", TASK_UMIDITYACTUATOR_NAME, statusUmidityActuator.usStackHighWaterMark);
            }
        }
        if (data.hndUmidityActuator != NULL)
        {
            TaskStatus_t statusUmidityActuator;
            vTaskGetInfo(data.hndUmidityActuator, &statusUmidityActuator, pdTRUE, eInvalid);
            if (data.hndUmidityActuator != NULL)
            {
                ESP_LOGI(TASK_MONITOR_NAME, "Task %s - STACK_LEFT %d", TASK_UMIDITYACTUATOR_NAME, statusUmidityActuator.usStackHighWaterMark);
            }
        }
        if (data.hndDisplay != NULL)
        {
            TaskStatus_t statusDisplay;
            vTaskGetInfo(data.hndDisplay, &statusDisplay, pdTRUE, eInvalid);
            if (data.hndDisplay != NULL)
            {
                ESP_LOGI(TASK_MONITOR_NAME, "Task %s - STACK_LEFT %d", TASK_DISPLAY_NAME, statusDisplay.usStackHighWaterMark);
            }
        }

        vTaskDelay(TASK_DEFAULTWAITTIME * 500);
    }
}