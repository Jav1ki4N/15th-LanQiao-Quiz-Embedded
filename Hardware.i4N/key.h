#ifndef _KEY_H
#define _KEY_H

#include "linker.h"

typedef struct
{
    uint8_t key_state;    //0: detected pressed 1: Confirm single press
                          //2: released 3:Confirm hold

    bool     key_level;   //raw state read from gpio
    bool     single_flag; //is key pressed singlely
    bool     double_flag; //is key double clicked
    bool     hold_flag;   //is key held
    uint8_t time;        //how long would a key considered held
}key_t;

extern key_t Keys[4];
void key_proc();

#endif