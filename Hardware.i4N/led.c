#include "led.h"

void led_disp(uint16_t led,uint8_t state)
{
    if(state)HAL_GPIO_WritePin(GPIOC,led,GPIO_PIN_RESET);
    else HAL_GPIO_WritePin(GPIOC,led,GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
}
