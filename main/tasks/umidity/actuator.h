#include "defaults.h"

#include "freertos/task.h"

#include "esp_log.h"

#define TASK_UMIDITYACTUATOR_NAME "umidityactuator"
#define TASK_UMIDITYACTUATOR_STACKSIZE 2048

void task_umidityactuator(void *pvParameters)
{
    ESP_LOGI(TASK_UMIDITYACTUATOR_NAME, "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}