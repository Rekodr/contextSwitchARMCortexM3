/* 
 @Athor: Recodeo Rekod
 @Class: EGR 424
 @Instructor: Dr. Parikh
*/ 

#include <stdio.h>
#include "core.h"
#include "rit128x96x4.h"




void thread1(void)
{
  while(1){
      if (lock_acquire(&threadlock)) {
          iprintf("I am thread Uart1\r\n");
          lock_release(&threadlock);   //release the peripheral
      }
      yield();
  }
}

void thread2(void)
{
  while(1){
      if (lock_acquire(&threadlock)) {
          iprintf("I am thread Uart2\r\n");
          lock_release(&threadlock);   //release the peripheral
      }
      yield();
  }
}

void thread3(void)
{
  unsigned int count = 0;
  for(count = 0;  count <  900000; count++); 
  while(1){
        if (lock_acquire(&scrlock)){
            for(count = 0;  count <  5000000; count++);
            for(count = 0;  count <  5000000; count++); 
            RIT128x96x4Clear(); 
            yield();
            for(count = 0;  count <  5000000; count++);  
            for(count = 0;  count <  5000000; count++);  
            RIT128x96x4StringDraw("HOLA THIS THREAD 3",10,  30, 15);
            lock_release(&scrlock);   //release the peripheral
        }
        yield(); 
  }
}

void thread4(void)
{
  unsigned int count = 0, c = 0;
  char n[50];
  for(count=0; c <50; c++)
    n[count] = '\0';  
  c = 0;   
  
  for(count = 0;  count <  900000; count++); 

  while(1){

        if (lock_acquire(&scrlock)){
            for(count = 0;  count <  5000000; count++);
            for(count = 0;  count <  5000000; count++); 
            RIT128x96x4Clear(); 
            sprintf(n, "T4 cnt: %d", c++); 
            if(c > 100000)
              c = 0; 
            for(count = 0;  count <  5000000; count++);  
            for(count = 0;  count <  5000000; count++);  
            RIT128x96x4StringDraw(n,0,  50, 10);
            lock_release(&scrlock);   //release the peripheral
        }
        yield(); 
  }
}