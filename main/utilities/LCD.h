#include <stdio.h>
#include <driver/gpio.h>
#include <hal/spi_types.h>
#include "driver/spi_common.h"
#include "driver/spi_master.h"

#define ILI9481
#define CS GPIO_NUM_5
#define RESET GPIO_NUM_21
#define DC_RS GPIO_NUM_19
#define MOSI GPIO_NUM_23
#define SCK GPIO_NUM_18
#define LED GPIO_NUM_22
#define MISO -1
#define T_CLK GPIO_NUM_17
#define T_CS GPIO_NUM_16
#define T_DIN GPIO_NUM_15
#define T_DO GPIO_NUM_14
#define T_IRQ GPIO_NUM_33
#define GPIO_LEVEL_LOW 0
#define GPIO_LEVEL_HIGH 1

//MIPI command set 
#define NOP 0x00
#define SET_DISPLAY_ON 0x29
#define SET_DISPLAY_OFF 0x28
#define SOFT_RESET 0x01
#define ENTER_SLEEP_MODE 0x10
#define EXIT_SLEEP_MODE 0x11
#define SET_COLUMN_ADDRESS 0x2A
#define SET_PAGE_ADDRESS 0x2B
#define WRITE_MEMORY_START 0x2C
#define DISPLAY_MODE 0xB4
#define ENTER_NORMAL_MODE 0x13
#define ENTER_SLEEP_MODE 0x10
#define EXIT_SLEEP_MODE 0x11
#define IDLE_MODE_OFF 0x00
#define SET_ADDRESS_MODE 0x36
#define SET_PIXEL_FORMAT 0x3A

//Screen Dimensions, 320x480
#define COLUMN_MIN 0
#define COLUMN_MAX 0x13FH
#define PAGE_MIN 0
#define PAGE_MAX 0x01DF

//misc

#define NO_CMD_PARAMETER NULL
#define NO_CMD NULL

void initialize_lcd(void);
void draw_bitmap(u_int8_t x_begin, u_int8_t y_begin, u_int8_t x_end, u_int8_t y_end, u_int8_t r_value, u_int8_t g_value, u_int8_t b_value);
void lcd_cmd(u_int8_t command, u_int8_t parameter[], u_int8_t length);
