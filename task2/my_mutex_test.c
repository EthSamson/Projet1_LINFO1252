#include <stdio.h>
#include <stdlib.h>
#include "my_mutex_test.h"

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

