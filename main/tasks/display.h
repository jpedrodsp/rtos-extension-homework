#pragma once

#include "defaults.h"

#include "freertos/task.h"
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
} display_pvparameters_t;

ssd1306_handle_t setup_display(void)
{
    char umid[3] = "30";
    char temp[10] = "30 C";

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

    ssd1306_fill_rectangle(ssd1306_dev, 4, 3, 60, 21, 1);    // esquerda encima
    ssd1306_fill_rectangle(ssd1306_dev, 71, 3, 125, 21, 1);  // Direita encima
    ssd1306_fill_rectangle(ssd1306_dev, 4, 24, 60, 41, 1);   // esquerda meio
    ssd1306_fill_rectangle(ssd1306_dev, 71, 24, 125, 41, 1); // Direita meio
    ssd1306_fill_rectangle(ssd1306_dev, 4, 44, 125, 61, 1);  // baixo
    ssd1306_draw_char(ssd1306_dev, 5, 25, 'T', 16, 0);
    ssd1306_draw_string(ssd1306_dev, 15, 25, &temp, 16, 0);
    ssd1306_draw_char(ssd1306_dev, 5, 4, 'C', 16, 0);
    ssd1306_draw_char(ssd1306_dev, 72, 25, 'U', 16, 0);
    ssd1306_draw_string(ssd1306_dev, 80, 25, &umid, 16, 0);
    ssd1306_draw_char(ssd1306_dev, 96, 25, '%', 16, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_refresh_gram(ssd1306_dev);
    ssd1306_clear_screen(ssd1306_dev, 0x00);
    return ssd1306_dev;
}

void task_display(void *pvParameters)
{
    ssd1306_handle_t dev = ((display_pvparameters_t *)pvParameters)->dev;
    // QueueHandle_t hndDisplayQueue = ((display_pvparameters_t *)pvParameters)->hndDisplayQueue;
    ESP_LOGI(TASK_DISPLAY_NAME, "Task started");
    while (1)
    {
        vTaskDelay(TASK_DEFAULTWAITTIME * 100);
    }
}