#include <stdio.h>
#include <stdlib.h>

typedef struct my_mutex{
  int state;
}my_mutex;

void my_mutex_init(my_mutex *mutex){
  mutex->state = 0;
}

void my_mutex_lock(my_mutex *mutex){
  asm("enter:\t"
      "movl $1, %%eax\t;"
      "xchgl %%eax, %1\t;"
      "testl %%eax, %%eax\t;"
      "jnz enter\t;"
      "movl $1, %%eax\t;"
      "movl %%eax, %0;"
      : "=r" (mutex->state)
      : "r" (mutex->state)
      : "%eax"
      );
}

void my_mutex_unlock(my_mutex *mutex){
  mutex->state = 0;
}

int main(int argc, char *argv[]){
  my_mutex mutex;
  my_mutex_init(&mutex);
  my_mutex_lock(&mutex);
  printf("%d\n",mutex.state);
  my_mutex_unlock(&mutex);
  printf("%d\n",mutex.state);
  return EXIT_SUCCESS;
}
