#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/sync.h>

#define OUT_PIN 0
#define DELAY_MS 100

//Current: 199.9998ms
//Min: 199.9998ms
//Max: 199.9998ms
//Mean: 199.9998ms
//stdv: 0ns
//Wave count: 51
//Drift: (200 - 199.9998) * (3,600,000 / 199.9998) = 3.6 ms over 1 hour


//Current: 5.00002Hz
//Min: 4.99997Hz
//Max: 5.00002Hz
//Mean: 5.00002Hz
//stdv: 23.108uHz
//Wave count: 51

//Current: 50%
//Min: 50%
//Max: 50%
//Mean: 50%
//stdv: 0.00%
//Wave count: 51

int toggle = 1;
bool timer_callback(__unused struct repeating_timer *t)
{
    toggle = !toggle;
    gpio_put(OUT_PIN, toggle);
    return true;
}

int main(void)
{
    stdio_init_all();
    // Create a repeating timer that calls timer_callback.
    // If the delay is > 0 then this is the delay between the previous
    // callback ending and the next starting.
    // If the delay is negative (see below) then the next call to the
    // callback will be exactly 500ms after the start of the call to
    // the last callback
    repeating_timer_t timer;
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    add_repeating_timer_ms(-DELAY_MS, timer_callback, NULL, &timer);
    while(1) __nop();
    return 0;
}
