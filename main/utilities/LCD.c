#include <stdio.h>
#include <driver/gpio.h>
#include <utilities/LCD.h>
#include <esp_err.h>
#include "freertos/task.h"



u_int8_t display_status = 0;

spi_bus_config_t config = {
.mosi_io_num = MOSI,
.miso_io_num = MISO,
.sclk_io_num = SCK,
.max_transfer_sz = 0,
};

spi_device_interface_config_t dev_config = {
    .command_bits = 8,
    .address_bits = 8,
    .mode = 0,
    .clock_source = SPI2_HOST,
    .spics_io_num = CS,
    .clock_speed_hz = 1000000,
    .queue_size = 10

};

spi_device_handle_t handle;

void lcd_cmd(u_int8_t command, u_int8_t parameter[], u_int8_t size){

    if(command != NO_CMD){
    
    gpio_set_level(DC_RS, GPIO_LEVEL_LOW);

    u_int8_t comd[] = {command};

    spi_transaction_t cmd ={
        .length = 8,
        .tx_buffer = comd
    };
    ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &cmd));
    }
    
    if (parameter == NO_CMD_PARAMETER){
        return;
    }

    gpio_set_level(DC_RS, GPIO_LEVEL_HIGH);

    spi_transaction_t cmd_param = {
        .length = 8*size,
        .tx_buffer = parameter
    };

    ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &cmd_param));

}


void initialize_lcd(void){

    printf("spi init func\n");

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &config, SPI_DMA_CH_AUTO));

    printf("bus init\n");

    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &dev_config, &handle ));

    printf("bus add device\n");

    ESP_ERROR_CHECK(gpio_set_direction(DC_RS, GPIO_MODE_OUTPUT));
   
    lcd_cmd(EXIT_SLEEP_MODE, NO_CMD_PARAMETER, 0);

    vTaskDelay(200 / portTICK_PERIOD_MS);

    lcd_cmd(ENTER_NORMAL_MODE, NO_CMD_PARAMETER, 0);

    vTaskDelay(200 / portTICK_PERIOD_MS);

    printf("normal mode\n");

    vTaskDelay(200 / portTICK_PERIOD_MS);

}

/*
Set column address -> set page address -> write memory start -> image data
*/

void draw_bitmap(u_int8_t x_begin, u_int8_t y_begin, u_int8_t x_end, u_int8_t y_end, u_int8_t r_value, u_int8_t g_value, u_int8_t b_value){

    //column address set
    u_int8_t column_address[] = {0x00, x_begin, 0x00, x_end - x_begin};
    // ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_LOW));
    // ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &set_column));
    // ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_HIGH));
    // spi_transaction_t column_start = {
    //     .length = 4*sizeof(u_int8_t),
    //     .tx_buffer = column_address
    // };
    // ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &column_start));
    lcd_cmd(SET_COLUMN_ADDRESS, column_address, sizeof(column_address));
    printf("column address sent\n");

    //page address set
    u_int8_t page_address[] = {0x00, y_begin, 0x00, y_end - y_begin};
    // ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_LOW));
    // ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &set_page));
    // ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_HIGH));
    // spi_transaction_t page_start = {
    //     .length = 4*sizeof(u_int8_t),
    //     .tx_buffer = page_address
    // };
    // ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &page_start));
    lcd_cmd(SET_PAGE_ADDRESS, page_address, sizeof(page_address));
    printf("page address sent\n");

    //write pixel data
    ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_LOW));
    ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &write_start));
    ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_HIGH));
    u_int8_t color_black[1000] = {0};

    spi_transaction_t black_pixels = {
        .length = 1000*sizeof(u_int8_t),
        .tx_buffer = color_black
    };
    ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &black_pixels));
    ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_LOW));
    ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &on));
    printf("pixel data sent\n");
    
}
