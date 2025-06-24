#include "key.h"

/***************************************************************************************/
uint8_t select = 1;

void add_val()
{
    if(select == 1)freq_jump+=100;
    if(select == 2)freq_limit+=100;
    if(select == 3)freq_calibration+=100;

    if(freq_jump>1000)freq_jump = 1000;
    if(freq_jump<100)freq_jump = 100;
    
    if(freq_limit>100000)freq_limit = 100000;
    if(freq_limit<1000)freq_limit = 1000;

    if(freq_calibration>1000)freq_calibration = 1000;
    if(freq_calibration<-1000)freq_calibration = -1000;
}

void dec_val()
{
    if(select == 1)freq_jump-=100;
    if(select == 2)freq_limit-=100;
    if(select == 3)freq_calibration-=100;

    if(freq_jump>1000)freq_jump = 1000;
    if(freq_jump<100)freq_jump = 100;
    
    if(freq_limit>100000)freq_limit = 100000;
    if(freq_limit<1000)freq_limit = 1000;

    if(freq_calibration>1000)freq_calibration = 1000;
    if(freq_calibration<-1000)freq_calibration = -1000;
}

void k3_func()
{
    if(mode == 1 || mode == 2)mode = -mode+3;
    if(mode == 3)
    {
        select++;
        if(select == 4)select = 1;
    }
}

void clear()
{
    if(mode == 4)
    {
        NDA = 0;
        NDB = 0;
        NHA = 0;
        NHB = 0;
    }
}

void k4_func()
{
    if(mode == 1 || mode == 2)mode = 3;
    else mode ++;
    if(mode == 5)mode = 1;   
}


/***************************************************************************************************************/

/* 100Hz T = 10ms */

key_t Keys[4] = {0,0,0,0,0};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3)
    {
        Keys[0].key_level = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
        Keys[1].key_level = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
        Keys[2].key_level = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);
        Keys[3].key_level = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

        for(int i=0;i<4;i++)
        {
            switch(Keys[i].key_state)
            {
                case 0: //detect pressed?
                {
                    if(Keys[i].key_level == 0) //yes
                    {
                        Keys[i].time = 0;      //reset time
                        Keys[i].key_state = 1; //Go to case 1(next state)
                    }
                    break;
                }

                /* from 0 to 1, 10ms Interrupt debouncing */

                case 1: //still pressed after debouncing?
                {
                    if(Keys[i].key_level == 0)    //yes
                    {
                        Keys[i].key_state = 2;    //Go to case 2
                                                  //check press type
                    }
                    else Keys[i].key_state = 0;        //if not, consider mispress
                    break;
                }
                case 2: //from pressed to realesed
                {
                    if(Keys[i].key_level == 1)    //released 
                    {
                        Keys[i].key_state = 0;    //state confirm , return

                        if(Keys[i].time < 70)
                        {
                            Keys[i].single_flag = 1;  //it's a single time press
                        }      
                    }
                    else
                    {
                        Keys[i].time++;            //while pressed time increase
                        if(Keys[i].time > 70)     //if press time > 1000ms or 1s
                            Keys[i].hold_flag = 1; // it's a hold press
                    }
                    break;
                }
                case 3:
                {
                    break;
                }
            }
        }
        
    }
}

void key_proc()
{
    if(Keys[0].single_flag)      // if key 1 is pressed singlely
    {
        add_val();
        //led_disp(l5,1);
        Keys[0].single_flag = 0; // single press complete
    }

    if(Keys[1].single_flag)      // if key 2 is pressed singlely
    {
        dec_val();
        //led_disp(l5,0);
        Keys[1].single_flag = 0; // single press complete
    }

    if(Keys[2].single_flag)
    {
        k3_func();
        //led_disp(l6,1);
        Keys[2].single_flag = 0; // single press complete
    }
    else if(Keys[2].hold_flag)
    {
        if(Keys[2].key_level == 1)
        {
            clear();
        }
        
        Keys[2].hold_flag = 0; // hold press complete
    }
    if(Keys[3].single_flag == 1)
    {
        k4_func();
        //led_disp(l6,0);
        Keys[3].single_flag = 0;
    } 
}
