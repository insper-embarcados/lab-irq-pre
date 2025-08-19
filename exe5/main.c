#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

const int BTN_PIN_R = 28;

volatile int g_event_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) {  // fall edge
        if (gpio == BTN_PIN_R) g_event_flag = 1;
    } else {
        if (gpio == BTN_PIN_R) g_event_flag = 0;
    }
}

int main() {
    stdio_init_all();

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R,
                                       GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE,
                                       true, &btn_callback);

    while (true) {
        if (g_event_flag) {
            sleep_ms(800);
            if (g_event_flag == 0)
                printf("Aperto curto!\n");
            else
                printf("Aperto longo!\n");

            g_event_flag = 0;
        }
    }
}
