#include <stdio.h>
#include <pico/stdlib.h>

//Current: 199.9998ms
//Min: 199.9998ms
//Max: 200.0035ms
//Mean: 199.9998ms
//stdv: 814ns
//Wave count: 59
//Drift: (200 - 199.9998) * (3,600,000 / 199.9998) = 3.6 ms over 1 hour

//Current: 5.00002Hz
//Min: 4.99Hz
//Max: 5Hz
//Mean: 5.00002Hz
//stdv: 27.436uHz
//Wave count: 59

//Current: 50%
//Min: 50%
//Max: 50%
//Mean: 50%
//stdv: 0.00%
//Wave count: 59


#define OUT_PIN 0
#define DELAY_MS 100

int main(void)
{
    int toggle = 0;
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    while (true) {
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        sleep_ms(DELAY_MS);
    }
}
