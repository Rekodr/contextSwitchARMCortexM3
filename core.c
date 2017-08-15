/* 
 @Athor: Recodeo Rekod
 @Class: EGR 424
 @Instructor: Dr. Parikh
*/ 

#include "core.h"

extern void threadStarter(void); 

// // This function is implemented in assembly language. It sets up the
// // initial jump-buffer (as would setjmp()) but with our own values
// // for the stack (passed to createThread()) and LR (always set to
// // threadStarter() for each thread).
extern void createThread(unsigned* state, char* stack) __attribute__((naked));
void createThread(unsigned* state, char* stack){
    asm volatile(
        "subs    r5, r1, #32\n"
        "stmea   r5!, { r0-r3, r12, r14 }\n"
        "mov     r1, r5\n"
        "ldr     r2, .L0\n"
        "mov     r3, #1\n"
        "lsls    r3, r3, #24\n"
        "stmea   r1!, {r2-r3}\n"
        "subs    r12, r1, #32\n"
        "stmea r0, {r4-r12}\n"
        "bx lr\n"
        ".L0:\n"
        ".word threadStarter"      
    );
}

/*
* @Description: This function set the lock to 0.
* @Param[in]:   *lock   pointer to the lock variable.
* @Param[out]:  *lock   *lock set to 0.
*/
void lock_release(unsigned *lock)
{
    *lock = 1;  /*set *lock to 0*/
}

/*
* @Description: This function initialize the lock to 0.
* @Param[in]:   *lock   pointer to the lock variable.
* @Param[out]:  *lock   *lock set to 0.
*/
void lock_init(unsigned *lock)
{
  *lock = 1;
}

/*
* @Description: This function initialize the lock to 0.
* @Param[in]:   *lock   pointer to the lock variable.
* @Param[out]:  *lock   if *lock is 0 then *lock is set to 1.
* @return:      0 if *lock is 1 otherwise return 1.  
*/
extern unsigned lock_acquire(unsigned *lock) __attribute__((naked));
unsigned lock_acquire(unsigned *lock){
    asm volatile(
        "mov r1, #0\n"
        "ldrex r2, [r0]\n"
        "cmp r2, r1\n"
        "itt ne\n"
        "STREXNE r2, r1, [r0]\n"
        "cmpne r2, #1\n"
        "beq 1f\n"
        "mov  r0, #1\n"
        "bx lr\n"
        "1:\n"
        "clrex\n"
        "mov r0, #0\n"
        "bx lr"
    );
}