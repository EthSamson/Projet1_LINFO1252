#ifndef _TASK2_1_
#define _TASK2_1_

/**
 * structure mutex
 */
typedef struct my_mutex{
  int state;
}my_mutex;

/**
 * initialise le mutex à 0
 * @mutex : pointeur vers le mutex à initialiser
 */ 
void my_mutex_init(my_mutex *mutex);

/**
 * fonction de verrouillage (test_and_test_and_set)
 * @mutex : mutex à verrouiller
 */
void my_mutex_testlock(my_mutex *mutex);

/**
 * fonction de verrouillage du mutex (test_and_set)
 * @mutex : mutex à verrouiller
 */
void my_mutex_lock(my_mutex *mutex);

/**
 * fonction de déverrouillage du mutex
 * @mutex : mutex à déverrouiller
 */
void my_mutex_unlock(my_mutex *mutex);

#endif
