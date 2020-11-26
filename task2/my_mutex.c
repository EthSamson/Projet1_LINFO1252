#include <stdio.h>
#include <stdlib.h>
#include "my_mutex.h"

void my_mutex_init(my_mutex *mutex){
  mutex->state = 0;
}

void my_mutex_lock(my_mutex *mutex){
  asm("enter:\t"
      "movl $1, %%eax\t;"
      "xchgl %%eax, %1\t;"
      "testl %%eax, %%eax\t;"
      "jnz enter\t;"
      : "=m" (mutex->state)
      : "m" (mutex->state)
      : "%eax"
      );
}

void my_mutex_testlock(my_mutex *mutex){ 
  while(test_and_set(mutex)){
    int i=mutex->state;
    while(i) i=mutex->state;
  }
}

void my_mutex_unlock(my_mutex *mutex){
  asm("movl $0, %%eax;"
      "xchgl %%eax,%0;"
      : "=m" (mutex->state)
      :"m" (mutex->state)
      : "%eax","%ebx"
      );
}

int test_and_set(my_mutex *mutex){
  int i;
  asm("movl $1, %%eax;"
      "xchgl %%eax, %[output0];"
      "movl %%eax, %[output1];"
      : [output0] "=m" (mutex->state), [output1] "=m" (i)
      : "m" (mutex->state)
      : "%eax"
      );
  return i;
}

