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

/**
 * test_and_set qui ne boucle pas utilisé par testlock
 * @return = 0 si mutex->state = 0 (càd mutex en mode non bloquant)
 *         = 1 si mutex->state = 1 (càd mutex en mode bloquant)
 */
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

void my_mutex_testlock(my_mutex *mutex){ 
  while(test_and_set(mutex)){
    int i=mutex->state;
    while(i) i=mutex->state;
  }
}