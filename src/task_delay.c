#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>

#define OUT_PIN 0
#define DELAY_MS 100

//Current: 200ms
//Min: 200ms
//Max: 200ms
//Mean: 200ms
//stdv: 810ns
//Wave count: 30


//Current: 5Hz
//Min: 5Hz
//Max: 5Hz
//Mean: 5Hz
//stdv: 13.34uHz
//Wave count: 35

//Current: 50%
//Min: 50%
//Max: 50%
//Mean: 50%
//stdv: 0.00%
//Wave count: 36

void main_task(__unused void *params)
{
    int toggle = 0;
    while (1) {
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

int main(void)
{
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    const char *rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &task);
    vTaskStartScheduler();
    return 0;
}
