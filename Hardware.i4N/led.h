#ifndef _LED_H
#define _LED_H

#include "linker.h"

#define l8 GPIO_PIN_15
#define l7 GPIO_PIN_14
#define l6 GPIO_PIN_13
#define l5 GPIO_PIN_12
#define l4 GPIO_PIN_11
#define l3 GPIO_PIN_10
#define l2 GPIO_PIN_9
#define l1 GPIO_PIN_8

void led_disp(uint16_t led,uint8_t state);

#endif
