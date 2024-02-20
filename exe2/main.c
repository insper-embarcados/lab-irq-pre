#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN_R = 28; 
const int LED_PIN_R = 4; 

volatile int flag_f_r = 0 ;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) {   // fall edge
        flag_f_r = 1;
    }
}

int main() {
  stdio_init_all();

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(BTN_PIN_R,
                                     GPIO_IRQ_EDGE_FALL,
                                     true,
                                     &btn_callback);

  int flag_led = 0;
  while (true) {

    if(flag_f_r){
        flag_f_r = 0;
        flag_led =! flag_led;
        gpio_put(LED_PIN_R, flag_led);
    }
  }
}
