#ifndef _TASK2_4_
#define _TASK2_4_
#include "my_mutex.h"

/**
 * structure semaphore
 * mutex pour bloquer les changements de current_state
 */
typedef struct my_sem{
  int current_state;
  my_mutex mutex;
}my_sem;

/**
 * fonction d'initialisation de my_sem
 */
void my_sem_init(my_sem *sem, int nb);

/**
 * équivalent à sem_wait POSIX
 */
void my_sem_wait(my_sem *sem);

/**
 * équivalent à sem_post POSIX
 */
void my_sem_post(my_sem *sem);

#endif
