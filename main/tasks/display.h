#include "defaults.h"

#include "freertos/task.h"

#include "esp_log.h"

#define TASK_DISPLAY_NAME "display"
#define TASK_DISPLAY_STACKSIZE 2048

void task_display(void *pvParameters)
{
    ESP_LOGI(TASK_DISPLAY_NAME, "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}