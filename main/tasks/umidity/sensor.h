#include "defaults.h"

#include "freertos/task.h"

#include "esp_log.h"

#define TASK_UMIDITYSENSOR_NAME "umiditysensor"
#define TASK_UMIDITYSENSOR_STACKSIZE 2048

void task_umiditysensor(void *pvParameters)
{
    ESP_LOGI(TASK_UMIDITYSENSOR_NAME, "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}