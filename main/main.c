#include <stdio.h>
#include <utilities/LCD.h>
#include "freertos/task.h"




void app_main(void)
{
    printf("main\n");

    initialize_lcd();
    vTaskDelay(100);
    printf("init completed\n");

    draw_bitmap(0, 0, 10, 100, 0, 0, 0);
    printf("bitmap drawn\n"); 
    vTaskDelay(500);
    
}