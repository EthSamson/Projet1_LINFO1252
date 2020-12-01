#include <stdio.h>
#include <stdlib.h>
#include "my_mutex.h"

void my_mutex_init(my_mutex *mutex){
  mutex->state = 0;
}

//adaptation du code assembleur vu en leçon 8
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

//on se sert aussi de xchg pour unlock en mode bloquant
void my_mutex_unlock(my_mutex *mutex){
  asm("movl $0, %%eax;"
      "xchgl %%eax,%0;"
      : "=m" (mutex->state)
      :"m" (mutex->state)
      : "%eax"
      );
}

void my_mutex_testlock(my_mutex *mutex){
  int i=1;
  while(i){
    asm("movl $1, %%eax;"
      "xchgl %%eax, %[output0];"
      "movl %%eax, %[output1];"
      : [output0] "=m" (mutex->state), [output1] "=m" (i)
      : "m" (mutex->state)
      : "%eax"
      );
    while(i) i = mutex->state;
  }
}
