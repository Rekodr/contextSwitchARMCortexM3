/* 
 @Athor: Recodeo Rekod
 @Class: EGR 424
 @Instructor: Dr. Parikh
*/ 

#include <stdlib.h>
#include "kernel.h"
#include "systick.h"
#include "core.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "inc/lm3s6965.h"

//#include "driverlib/"
// These are the external user-space threads. In this program, we create
// the threads statically by placing their function addresses in
// threadTable[]. A more realistic kernel will allow dynamic creation
// and termination of threads.
extern void thread1(void);
extern void thread2(void);
extern void thread3(void);
extern void thread4(void); 


extern void createThread(unsigned* state, char* stack);

static thread_t threadTable[] = {
  thread1,
  thread2,
  thread3,
  thread4
};
#define NUM_THREADS (sizeof(threadTable)/sizeof(threadTable[0]))


static threadStruct_t* presentThread; 
static int save = 0; 
static threadStruct_t threads[NUM_THREADS]; // the thread table
unsigned currThread;    // The currently active thread
unsigned threadIndexes; 
unsigned threadlock;
unsigned scrlock;




void yield(void){
  asm volatile("svc #200");
}

void threadStarter(void){
  // Call the entry point for this thread. The next line returns
  // only when the thread exits.
  (*(threadTable[currThread]))();

  // Do thread-specific cleanup tasks. Currently, this just means marking
  // the thread as inactive. This function runs in user thread context.
  threads[currThread].active = 0;
  
  // This yield returns to the scheduler and never returns back since
  // the scheduler identifies the thread as inactive.
  yield();
}

void init_kernel(void){
    threadIndexes = -1;
    currThread = -1;
    lock_init(&scrlock);
    lock_init(&threadlock);
    // Create all the threads and allocate a stack for each one
  for (int i=0; i < NUM_THREADS; i++) {
    // Mark thread as runnable
    threads[i].active = 1;

    // Allocate stack
    threads[i].stack = (char *)malloc(STACK_SIZE) + STACK_SIZE;
    if (threads[i].stack == 0) {
      exit(1);
    }

    createThread(threads[i].state, threads[i].stack);
  }
  setupSystick();
  IntMasterEnable(); 

  asm volatile("svc #200");
}

void TaskSelect(){

  IntMasterDisable();
  NVIC_ST_CURRENT_R = 0;
  unsigned int i = NUM_THREADS ; 
  //registering the current thread
  if(save == 1)  
    presentThread = &threads[currThread]; 

  do {
        // Round-robin scheduler
        if (++currThread == NUM_THREADS) {
          currThread = 0;
        }

        if (threads[currThread].active) {
          break;        
        } else {
          i--;
        }
  } while (i > 0);

  if(save == 0){
       presentThread = &threads[currThread]; 
       asm volatile ("msr psp, %0" : : "r" (presentThread->state[8]));
      save = 1; 
  }
   IntMasterEnable();
  HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PEND_SV;
}


void SwitchContext(){
  
 // IntMasterDisable();
  asm volatile("mrs r12, psp\n");
  asm volatile("stm %0, {r4-r12}" : : "r" (presentThread->state));
  // if(presentThread->active == 0){
  //   free(presentThread->stack); 
  // }
  asm volatile("ldm %0, {r4-r12}" : : "r" (threads[currThread].state));
  //IntMasterEnable();
  asm volatile(
            "msr psp, r12\n"
            "mrs r0, CONTROL\n"
            "orr r0, 0x1\n"
            "msr CONTROL, r0\n"
            "isb\n"
            "movw lr, #0xfffd\n"
            "movt lr, #0xffff\n"
            "bx lr"
  );
}
