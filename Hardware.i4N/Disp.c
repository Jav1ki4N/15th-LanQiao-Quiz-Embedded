#include "Disp.h"

uint8_t mode = 1;

uint32_t  freq_jump = 1000;     //PD
uint32_t  freq_limit = 5000;    //PH
int32_t   freq_calibration = 0; //PX

int32_t freq_pre_A;
int32_t freq_pre_B;

uint8_t NDA = 0;
uint8_t NDB = 0;
uint8_t NHA = 0;
uint8_t NHB = 0;

char CH[30];

int32_t calibration(uint32_t freq, int32_t cali,uint8_t channel)
{
    int32_t freq_temp = (int32_t)freq + cali;
    return freq_temp;
}

void isExceedLimitOrJump(int32_t freq,int32_t freq_p,uint8_t channel)
{
    int32_t freq_change = freq-freq_p;
    if(freq_change < 0)freq_change *= -1;
    if(freq_change > freq_jump)
    {
        if(channel == 1)NDA++;
        else if(channel == 2)NDB++;
    }

    if(NDA>=3 || NDB>=3)
    {
        led_disp(l8,1);
    }
    else led_disp(l8,0);
    
    if(freq<0)return;
    else if(freq > freq_limit && freq_p < freq_limit)
    {
        if(channel == 1)NHA++;
        else if(channel == 2)NHB++;
    }
    
    if(channel ==1)
    {
        if(freq > freq_limit)led_disp(l2,1);
        else led_disp(l2,0);
    }
    if(channel == 2)
    {
        if(freq > freq_limit)led_disp(l3,1);
        else led_disp(l3,0);
    }
}

void freq_proc(int32_t freq,uint8_t channel)
{
    if(channel == 1)
    {
        if(freq>1000)
             sprintf(CH,"     A=%.2fKHz     ",(float)(freq/1000.0f));
        else if(freq<0)
             sprintf(CH,"     A=NULL     ");
        else sprintf(CH,"     A=%dHz     ",freq);
    }
    else if (channel == 2)
    {
        if(freq>1000)
             sprintf(CH,"     B=%.2fKHz     ",(float)(freq/1000.0f));
        else if(freq<0)
             sprintf(CH,"     B=NULL     ");
        else sprintf(CH,"     B=%dHz     ",freq);
    }
}

void period_proc(int32_t freq,uint8_t channel)
{
    double period = (double)(1/(double)freq);
    if(channel == 1)
    {
        if(freq<0)sprintf(CH,"     A=NULL     ");
        else if(period > 0.001)
             sprintf (CH,"     A=%.2fmS     ",(float)(period*1000.0f));
        else sprintf(CH,"     A=%duS     ",(uint32_t)(period*1000000.0f));
    }
    else if (channel == 2)
    {
        if(freq<0)sprintf(CH,"     B=NULL     ");
        else if(period > 0.001)
             sprintf (CH,"     B=%.2fmS     ",(float)(period*1000.0f));
        else sprintf(CH,"     B=%duS     ",(uint32_t)(period*1000000.0f));
    }
}

void disp_proc()
{
    switch(mode)
    {
        case 1:
        {           
            uint32_t freq_A = calibration(freq_r40,freq_calibration,1);
            uint32_t freq_B = calibration(freq_r39,freq_calibration,2);

            isExceedLimitOrJump(freq_A,freq_pre_A,1);
            isExceedLimitOrJump(freq_B,freq_pre_B,2);
            
            LCD_DisplayStringLine(Line1,(uint8_t*)"        DATA"); 

            freq_proc(freq_A,1);
            LCD_DisplayStringLine(Line3,(uint8_t*)CH);
            freq_proc(freq_B,2);
            LCD_DisplayStringLine(Line4,(uint8_t*)CH);
            
            LCD_DisplayStringLine(Line5,(uint8_t*)"                        ");
            LCD_DisplayStringLine(Line6,(uint8_t*)"                        ");

            freq_pre_A = freq_A;
            freq_pre_B = freq_B;

            led_disp(l1,1);

            break; 
        }

        case 2:
        {
            uint32_t freq_A = calibration(freq_r40,freq_calibration,1);
            uint32_t freq_B = calibration(freq_r39,freq_calibration,2);

            isExceedLimitOrJump(freq_A,freq_pre_A,1);
            isExceedLimitOrJump(freq_B,freq_pre_B,2);

            LCD_DisplayStringLine(Line1,(uint8_t*)"        DATA");

            period_proc(freq_A,1);
            LCD_DisplayStringLine(Line3,(uint8_t*)CH);
            period_proc(freq_B,2);
            LCD_DisplayStringLine(Line4,(uint8_t*)CH); 
            
            LCD_DisplayStringLine(Line5,(uint8_t*)"                        ");
            LCD_DisplayStringLine(Line6,(uint8_t*)"                        ");

            freq_pre_A = freq_A;
            freq_pre_B = freq_B;

            led_disp(l1,1);

            break;
        }

        case 3:
        {
            led_disp(l1,0);

            uint32_t freq_A = calibration(freq_r40,freq_calibration,1);
            uint32_t freq_B = calibration(freq_r39,freq_calibration,2);

            isExceedLimitOrJump(freq_A,freq_pre_A,1);
            isExceedLimitOrJump(freq_B,freq_pre_B,2);

            LCD_DisplayStringLine(Line1,(uint8_t*)"        PARA");
            sprintf(CH,"     PD=%dHz     ",freq_jump);
            LCD_DisplayStringLine(Line3,(uint8_t*)CH);
            sprintf(CH,"     PH=%dHz     ",freq_limit);
            LCD_DisplayStringLine(Line4,(uint8_t*)CH);
            sprintf(CH,"     PX=%dHz     ",freq_calibration);
            LCD_DisplayStringLine(Line5,(uint8_t*)CH);
            LCD_DisplayStringLine(Line6,(uint8_t*)"                        ");

            freq_pre_A = freq_A;
            freq_pre_B = freq_B;

            break;
        }

        case 4:
        {
            led_disp(l1,0);

            uint32_t freq_A = calibration(freq_r40,freq_calibration,1);
            uint32_t freq_B = calibration(freq_r39,freq_calibration,2);

            isExceedLimitOrJump(freq_A,freq_pre_A,1);
            isExceedLimitOrJump(freq_B,freq_pre_B,2);

            LCD_DisplayStringLine(Line1,(uint8_t*)"        RECD");
            sprintf(CH,"     NDA=%d     ",NDA);
            LCD_DisplayStringLine(Line3,(uint8_t*)CH);
            sprintf(CH,"     NDB=%d     ",NDB);
            LCD_DisplayStringLine(Line4,(uint8_t*)CH);
            sprintf(CH,"     NHA=%d     ",NHA);
            LCD_DisplayStringLine(Line5,(uint8_t*)CH);
            sprintf(CH,"     NHB=%d     ",NHB);
            LCD_DisplayStringLine(Line6,(uint8_t*)CH);
            
            freq_pre_A = freq_A;
            freq_pre_B = freq_B;

            break;
        }
		
    }
}