#include <stdio.h>
#include <driver/gpio.h>
#include <utilities/LCD.h>
#include <esp_err.h>


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

  u_int8_t tx_buffer[] = {SET_DISPLAY_OFF, SET_DISPLAY_ON, ENTER_NORMAL_MODE, EXIT_SLEEP_MODE, ENTER_SLEEP_MODE };

    spi_transaction_t off = {
        .length = 8,
        .tx_buffer = &tx_buffer[0]
    };
    spi_transaction_t on = {
        .length = 8,
        .tx_buffer = &tx_buffer[1]
    };
    spi_transaction_t normal_mode = {
        .length = 8,
        .tx_buffer = &tx_buffer[2]
    };

    spi_transaction_t exit_sleep_mode = {
        .length = 8,
        .tx_buffer = &tx_buffer[3]
    };
     spi_transaction_t enter_sleep_mode = {
        .length = 8,
        .tx_buffer = &tx_buffer[4]
    };






   

}

void initialize_lcd(void){

    printf("spi init func\n");
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &config, SPI_DMA_CH_AUTO));
    printf("bus init\n");
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &dev_config, &handle ));
    printf("bus add device\n");
    ESP_ERROR_CHECK(gpio_set_direction(DC_RS, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(DC_RS, GPIO_LEVEL_LOW));
    ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &exit_sleep_mode));
    ESP_ERROR_CHECK(spi_device_polling_transmit(handle, &normal_mode));
    printf("normal mode\n");
}

/*
Set column address -> set page address -> write memory start -> image data
*/

void draw_bitmap(u_int8_t x_begin, u_int8_t y_begin, u_int8_t x_end, u_int8_t y_end, u_int8_t r_value, u_int8_t g_value, u_int8_t b_value){



}
