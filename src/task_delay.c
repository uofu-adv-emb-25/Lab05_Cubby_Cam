#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>

#define OUT_PIN 0
#define DELAY_MS 100

//Current: 199.9998ms
//Min: 199.9998ms
//Max: 200.035ms
//Mean: 199.9998ms
//stdv: 518ns
//Wave count: 52
//Drift: (200 - 199.9998) * (3,600,000 / 199.9998) = 3.6 ms over 1 hour


//Current: 5.00002Hz
//Min: 4.99992Hz
//Max: 5.00002Hz
//Mean: 5.00001Hz
//stdv: 24.946uHz
//Wave count: 52

//Current: 50%
//Min: 50%
//Max: 50%
//Mean: 50%
//stdv: 0.00%
//Wave count: 52

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
