#include "defaults.h"

#include "freertos/task.h"

#include "esp_log.h"

#define TASK_UMIDITYACTUATOR_NAME "umidityactuator"
#define TASK_UMIDITYACTUATOR_STACKSIZE 2048
#define TASK_UMIDITYACTUATOR_OUT_PIN 24

void task_umidityactuator(void *pvParameters)
{
    ESP_LOGI(TASK_UMIDITYACTUATOR_NAME, "Task started");
    while(1)
    {
        // TODO: Value is received from a queue. Implement it.
        ESP_LOGW(TASK_UMIDITYACTUATOR_NAME, "Value is received from a queue. It is not implemented yet");
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}