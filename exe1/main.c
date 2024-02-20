#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN_R = 28; 

volatile int flag_f_r = 0 ;
volatile int flag_r_r = 0 ;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) {         // fall edge
        flag_f_r = 1;
    } else if (events == 0x8) {  // rise edge
        flag_r_r = 1;
    }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(BTN_PIN_R,
                                     GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
                                     true,
                                     &btn_callback);

  while (true) {

    if(flag_f_r){
        printf("fall \n");
        flag_f_r = 0;
    }

    if(flag_r_r){
        printf("rise \n");
        flag_r_r = 0;
    }

  }
}
