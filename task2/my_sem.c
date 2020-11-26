#include <stdio.h>
#include <stdlib.h>
#include "my_sem.h"

void my_sem_init(my_sem *sem, int nb){
  sem->max_state=nb;
  sem->current_state=nb;
  my_mutex_init(&(sem->mutex));
}

int test_and_set2(my_sem *sem){
  my_mutex_testlock(&(sem->mutex));
  if(sem->current_state == 0){
    my_mutex_unlock(&(sem->mutex));
    return 1;
  }
  else{
    sem->current_state = (sem->current_state) - 1;
    my_mutex_unlock(&(sem->mutex));
    return 0;
  }
}

void my_sem_wait(my_sem *sem){
  while(test_and_set2(sem)){
    int i = sem->current_state;
    while(i==0) i=sem->current_state;
  }
}

void my_sem_post(my_sem *sem){
  my_mutex_testlock(&(sem->mutex));
  sem->current_state = sem->current_state + 1;
  my_mutex_unlock(&(sem->mutex));
}

