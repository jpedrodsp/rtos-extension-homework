#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tasks/umidity/sensor.h"
#include "tasks/umidity/actuator.h"
#include "tasks/display.h"
#include "defaults.h"

#include "esp_log.h"

typedef struct inithw_s
{
    ssd1306_handle_t hndDisplayDevice;
} inithw_t;

inithw_t init_hw(void)
{
    inithw_t inithw;
    // Configure PINs/Connections for DHT22
    {
        // Not needed if using DHT Library
    }
    // Configure PINs/Connections for Display
    {
        inithw.hndDisplayDevice = setup_display();
    }
    // Configure PINs/Connections for Actuator
    {
    }
    return inithw;
}

void app_main(void)
{
    inithw_t config = init_hw();
    
    // Create Umidity Sensor Task
    #ifdef TASK_UMIDITYSENSOR_ENABLE
    #if TASK_UMIDITYSENSOR_ENABLE == 1
    TaskHandle_t hndUmiditySensorTask;
    xTaskCreate(task_umiditysensor, TASK_UMIDITYSENSOR_NAME, TASK_UMIDITYSENSOR_STACKSIZE, NULL, 1, &hndUmiditySensorTask);
    #endif
    #endif
    
    // Create Display Task
    #ifdef TASK_DISPLAY_ENABLE
    #if TASK_DISPLAY_ENABLE == 1
    TaskHandle_t hndDisplayTask;
    display_pvparameters_t display_pvparameters = {
        .dev = config.hndDisplayDevice};
    xTaskCreate(task_display, TASK_DISPLAY_NAME, TASK_DISPLAY_STACKSIZE, &display_pvparameters, 1, &hndDisplayTask);
    #endif
    #endif

    // Create Umidity Actuator Task
    #ifdef TASK_UMIDITYACTUATOR_ENABLE
    #if TASK_UMIDITYACTUATOR_ENABLE == 1
    TaskHandle_t hndUmidityActuatorTask;
    xTaskCreate(task_umidityactuator, TASK_UMIDITYACTUATOR_NAME, TASK_UMIDITYACTUATOR_STACKSIZE, NULL, 1, &hndUmidityActuatorTask);
    #endif
    #endif
}