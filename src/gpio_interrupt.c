#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/sync.h>

#define IN_PIN 27
#define OUT_PIN 0
#define DELAY_MS 50

//Delay between the sync signal and the output:
//Current: 3.2us
//Min: 3.2us
//Max: 4.8us
//Mean: 3.2us
//stdv: 512us
//Wave count: 16

//Delay between the sync signal and the output with 10000ms delay:
//Current: 5.7us
//Min: 5.7us
//Max: 5.7us
//Mean: 5.7us
//stdv: 512us
//Wave count: 16


int toggle = 1;
void irq_callback(uint gpio, uint32_t event_mask)
{
    if (gpio != IN_PIN) return;
    sleep_ms(DELAY_MS);
    toggle = !toggle;
    if (event_mask & GPIO_IRQ_EDGE_RISE) {
        gpio_put(OUT_PIN, true);
    } else if (event_mask & GPIO_IRQ_EDGE_FALL) {
        gpio_put(OUT_PIN, false);
    }
}

int main(void)
{
    stdio_init_all();

    gpio_init(IN_PIN);
    gpio_set_dir(IN_PIN, GPIO_IN);

    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    gpio_set_irq_enabled_with_callback(IN_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL , true, irq_callback);
    while(1) __wfi();
    return 0;
}
