#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tasks/umidity/sensor.h"
#include "tasks/umidity/actuator.h"
#include "tasks/display.h"
#include "defaults.h"

#include "esp_log.h"

void init_hw(void)
{
    // Configure PINs/Connections for DHT22
    {

    }
    // Configure PINs/Connections for Display
    {

    }
    // Configure PINs/Connections for Actuator
    {

    }
}

void app_main(void)
{
    init_hw();
    // Create Umidity Sensor Task
    xTaskCreate(task_umiditysensor, TASK_UMIDITYSENSOR_NAME, TASK_UMIDITYSENSOR_STACKSIZE, NULL, 1, NULL);
    // Create Display Task
    xTaskCreate(task_display, TASK_DISPLAY_NAME, TASK_DISPLAY_STACKSIZE, NULL, 1, NULL);
    // Create Umidity Actuator Task
    xTaskCreate(task_umidityactuator, TASK_UMIDITYACTUATOR_NAME, TASK_UMIDITYACTUATOR_STACKSIZE, NULL, 1, NULL);
}