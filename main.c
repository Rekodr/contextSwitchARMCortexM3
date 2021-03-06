/* 
 @Athor: Recodeo Rekod
 @Class: EGR 424
 @Instructor: Dr. Parick

 this file is for testing.....
 */


#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include "inc/hw_memmap.h" 
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "rit128x96x4.h"
#include "inc/lm3s6965.h"
#include "driverlib/interrupt.h"
#include "kernel.h"

#include "core.h"

int t = 1; 
 
 int main(){

     // Setthe clocking to run directly from the crystal.
     SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ); 

    // Enable the peripherals used by this example.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Set GPIO A0 and A1 as UART pins.
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configure the UART for 115,200, 8-N-1 operation.
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                      (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                       UART_CONFIG_PAR_NONE));
    //GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT) ; 

    // Initialize the OLED display and write status.
    RIT128x96x4Init(1000000);
    RIT128x96x4StringDraw("Preject 2 Demo",       20,  0, 15);
    iprintf("Start testing.Testting......\r\n"); 
    init_kernel(); 
    while(1);

     return 0;
 }

