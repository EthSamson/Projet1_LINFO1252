#include <stdio.h>
#include <stdlib.h>
#include "task2_1.h"

int main(int argc, char *argv[]){
  my_mutex mutex;
  my_mutex_init(&mutex);
  my_mutex_lock(&mutex);
  printf("%d\n",mutex.state);
  my_mutex_unlock(&mutex);
  printf("%d\n",mutex.state);
  return EXIT_SUCCESS;
}
