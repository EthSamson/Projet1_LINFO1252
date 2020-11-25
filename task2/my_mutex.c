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

void my_mutex_unlock(my_mutex *mutex){
  asm("movl %0, %%eax;"
      "movl $0, %%ebx;"
      "xchgl %%eax,%%ebx;"
      "movl %%eax, %0;"
      : "=m" (mutex->state)
      :"m" (mutex->state)
      : "%eax","%ebx"
      );
}

