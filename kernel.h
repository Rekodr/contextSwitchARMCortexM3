/* 
 @Athor: Recodeo Rekod
 @Class: EGR 424
 @Instructor
*/ 
#ifndef _KERNEL_H_
#define _KERNEL_H_

#define STACK_SIZE 4096   // Amount of stack space for each thread

extern unsigned currThread;
// thread_t is a pointer to function with no parameters and
// no return value...i.e., a user-space thread.
typedef void (*thread_t)(void);

// This function is called from within user thread context. It executes
// a jump back to the scheduler. When the scheduler returns here, it acts
// like a standard function return back to the caller of yield().
void yield(void);

// This is the starting point for all threads. It runs in user thread
// context using the thread-specific stack. The address of this function
// is saved by createThread() in the LR field of the jump buffer so that
// the first time the scheduler() does a longjmp() to the thread, we
// start here.
void threadStarter(void);

// This function initializes the kernel;
void init_kernel(void);

// This is function select the next thread to run;
void TaskSelect(void); 
void SwitchContext(void);

#endif
