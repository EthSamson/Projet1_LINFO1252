#ifndef _TASK2_4_
#define _TASK2_4_
#include "my_mutex.h"
/**
 * structure semaphore
 */
typedef struct my_sem{
  int max_state;
  int current_state;
  my_mutex mutex;
}my_sem;

void my_sem_init(my_sem *sem, int nb);

void my_sem_wait(my_sem *sem);

void my_sem_post(my_sem *sem);

#endif
