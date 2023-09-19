#include "defaults.h"

#include "freertos/task.h"
#include "driver/gpio.h"

#include "ssd1306.h"

#include "esp_log.h"

#define TASK_DISPLAY_NAME "display"
#define TASK_DISPLAY_STACKSIZE 2048
#define TASK_DISPLAY_I2CPORT I2C_NUM_0 // defined in gpio.h

typedef struct display_pvparameters_s {
    ssd1306_handle_t dev;
} display_pvparameters_t;

ssd1306_handle_t setup_display(void)
{
    i2c_port_t i2cport = TASK_DISPLAY_I2CPORT;
    ssd1306_handle_t dev = ssd1306_create(i2cport, SSD1306_I2C_ADDRESS);
    ssd1306_init(dev);
    ssd1306_clear_screen(dev, false);
    ssd1306_refresh_gram(dev);
    return dev;
}

void task_display(void *pvParameters)
{
    ssd1306_handle_t dev = ((display_pvparameters_t *) pvParameters)->dev;
    ESP_LOGI(TASK_DISPLAY_NAME, "Task started");
    while(1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME);
    }
}