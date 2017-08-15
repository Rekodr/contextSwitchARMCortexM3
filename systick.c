/* 
 @Athor: Recodeo Rekod
 @Class: EGR 424
 @Instructor: Dr. Parick
 */

#include "systick.h"
#include "inc/lm3s6965.h"
#include "kernel.h"

#define TIMER_LOAD_VAL 0x1F40

void extern scheduler();

void setupSystick(){
    NVIC_ST_CTRL_R = 0; 
    NVIC_ST_RELOAD_R = TIMER_LOAD_VAL; 
    NVIC_ST_CURRENT_R = TIMER_LOAD_VAL; 
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC; 
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN; 
} 


