#include "IC.h"

uint32_t cap_val1,cap_val2;
uint32_t freq_r39;
uint32_t freq_r40;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) 
{
    if(htim->Instance == TIM16)
    {
        cap_val1 = HAL_TIM_ReadCapturedValue(&htim16,TIM_CHANNEL_1);
        TIM16->CNT = 0;
        freq_r39 = (SystemCoreClock) / ((TIM16->PSC+1)*cap_val1);
    }

    if(htim->Instance == TIM2)
    {
        cap_val2 = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);
        TIM2->CNT = 0;
        freq_r40 = (SystemCoreClock) / ((TIM2->PSC+1)*cap_val2);
    }
}
