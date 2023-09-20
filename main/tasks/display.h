#pragma once

#include "queues/umidity.h"
#include "defaults.h"

#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "ssd1306.h"

#include "esp_log.h"

#define TASK_DISPLAY_NAME "display"
#define TASK_DISPLAY_STACKSIZE 4096
// #define TASK_DISPLAY_I2CPORT I2C_NUM_1 // defined in gpio.h

#define I2C_MASTER_SCL_IO 22      /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 21      /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUM_1  /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000 /*!< I2C master clock frequency */

typedef struct display_pvparameters_s
{
    ssd1306_handle_t dev;
    QueueHandle_t hndUmiditySensorQueue;
} display_pvparameters_t;

void draw_rectangles(ssd1306_handle_t dev)
{
    ssd1306_fill_rectangle(dev, 4, 3, 60, 21, 1);    // esquerda encima
    ssd1306_fill_rectangle(dev, 71, 3, 125, 21, 1);  // Direita encima
    ssd1306_fill_rectangle(dev, 4, 24, 60, 41, 1);   // esquerda meio
    ssd1306_fill_rectangle(dev, 71, 24, 125, 41, 1); // Direita meio
    ssd1306_fill_rectangle(dev, 4, 44, 125, 61, 1);  // baixo
    ssd1306_draw_char(dev, 5, 25, 'T', 16, 0);
    ssd1306_draw_char(dev, 5, 4, 'C', 16, 0);
    ssd1306_draw_char(dev, 72, 25, 'U', 16, 0);
    ssd1306_draw_char(dev, 96, 25, '%', 16, 0);
}

ssd1306_handle_t setup_display(void)
{
    // char umid[3] = "30";
    // char temp[10] = "30 C";

    ssd1306_handle_t ssd1306_dev = NULL;

    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

    ssd1306_dev = ssd1306_create(I2C_MASTER_NUM, SSD1306_I2C_ADDRESS);

    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_refresh_gram(ssd1306_dev);
    ssd1306_clear_screen(ssd1306_dev, 0x00);
    return ssd1306_dev;
}

void task_display(void *pvParameters)
{
    display_pvparameters_t display_pvparameters = {
        .dev = NULL,
        .hndUmiditySensorQueue = NULL};
    display_pvparameters.dev = ((display_pvparameters_t *)pvParameters)->dev;
    display_pvparameters.hndUmiditySensorQueue = ((display_pvparameters_t *)pvParameters)->hndUmiditySensorQueue;
    if (display_pvparameters.dev == NULL)
    {
        ESP_LOGE(TASK_DISPLAY_NAME, "Error receiving display device from pvParameters");
        return;
    }
    if (display_pvparameters.hndUmiditySensorQueue == NULL)
    {
        ESP_LOGE(TASK_DISPLAY_NAME, "Error receiving queue from pvParameters");
        return;
    }

    umidityqueue_data_t data = {
        .umidity = 0,
        .temperature = 0};

    ESP_LOGI(TASK_DISPLAY_NAME, "Task started");
    while (1)
    {
        // Receive data from queue
        if (xQueueReceive(display_pvparameters.hndUmiditySensorQueue, &data, TASK_DEFAULTWAITTIME) == pdTRUE)
        {
            ESP_LOGI(TASK_DISPLAY_NAME, "Data received from queue: Umidity: %d%%, Temperature: %d°C", data.umidity / 10, data.temperature / 10);
            char umid[10];
            char temp[10];
            char status[68] = "Monitorando...";
            sprintf(umid, "%d%%", data.umidity / 10);
            sprintf(temp, "%d C", data.temperature / 10);
            ssd1306_clear_screen(display_pvparameters.dev, 0x00);
            draw_rectangles(display_pvparameters.dev);
            ssd1306_draw_string(display_pvparameters.dev, 15, 25, &temp, 16, 0);
            ssd1306_draw_string(display_pvparameters.dev, 80, 25, &umid, 16, 0);
            ssd1306_draw_string(display_pvparameters.dev, 5, 45, &status, 16, 0);
            ssd1306_refresh_gram(display_pvparameters.dev);
            xQueueReset(display_pvparameters.hndUmiditySensorQueue);
        }
        else
        {
            // Now you can use the data to update the display (data.umidity and data.temperature). We are using it to log the data to the console.
            ESP_LOGW(TASK_DISPLAY_NAME, "Error receiving data from queue: is queue empty? AVAILABLE/WAITING: %d/%d", uxQueueSpacesAvailable(display_pvparameters.hndUmiditySensorQueue), uxQueueMessagesWaiting(display_pvparameters.hndUmiditySensorQueue));
        }
        vTaskDelay(TASK_DEFAULTWAITTIME * 50);
    }
}