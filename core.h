/* 
 @Athor: Recodeo Rekod
 @Class: EGR 424
 @Instructor: Dr. Parikh
*/ 
#ifndef _CORE_H_
#define _CORE_H_


typedef struct {
  int active;           // non-zero means thread is allowed to run
  char *stack;          // pointer to TOP of stack (highest memory location)
  unsigned state[10];    // saved state of R4 to R11 and the process stack. 
} threadStruct_t;


extern unsigned threadlock;
extern unsigned scrlock;
extern unsigned lock_acquire(unsigned *lock); 
extern void lock_release(unsigned *lock);
extern void yield(void); 

void lock_release(unsigned *lock);
void lock_init(unsigned *lock);


#endif