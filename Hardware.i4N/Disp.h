#ifndef _DISP_H
#define _DISP_H

#include "linker.h"

extern uint8_t mode;

extern uint32_t  freq_jump;     //PD
extern uint32_t  freq_limit;    //PH
extern int32_t   freq_calibration; //PX

extern uint8_t NDA;
extern uint8_t NDB;
extern uint8_t NHA;
extern uint8_t NHB;

void disp_proc(void);

#endif