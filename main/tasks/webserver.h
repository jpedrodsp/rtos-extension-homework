#pragma once

#include "defaults.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TASK_WEBSERVER_NAME "monitor"
#define TASK_WEBSERVER_STACKSIZE 4096

typedef struct webserver_pvparameters_s
{
    int dummy;
} webserver_pvparameters_t;

void task_webserver(void *pvParameters)
{
    webserver_pvparameters_t data = *((webserver_pvparameters_t *)pvParameters);
    ESP_LOGI(TASK_WEBSERVER_NAME, "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME * 100);
    }
}