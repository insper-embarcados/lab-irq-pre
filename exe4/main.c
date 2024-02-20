#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

const int LED_PIN_R = 4;
const int LED_PIN_G = 6;

volatile int flag_f_r = 0;
volatile int flag_f_g = 0;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        if (gpio == BTN_PIN_R)
            flag_f_r = 1;
    } else if (events == 0x8) { // fall edge
        if (gpio == BTN_PIN_G)
            flag_f_g = 1;
    }
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);

    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R,
                                       GPIO_IRQ_EDGE_FALL,
                                       true,
                                       &btn_callback);

    gpio_set_irq_enabled(BTN_PIN_G,
                         GPIO_IRQ_EDGE_RISE,
                         true);

    int status_led_r = 0;
    int status_led_g = 0;

    while (true) {

        if (flag_f_r) {
            flag_f_r = 0;
            status_led_r = !status_led_r;
            gpio_put(LED_PIN_R, status_led_r);
        }

        if (flag_f_g) {
            flag_f_g = 0;
            status_led_g = !status_led_g;
            gpio_put(LED_PIN_G, status_led_g);
        }
    }
}
