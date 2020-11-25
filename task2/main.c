#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "my_mutex.h"

int nb_sections = 30;
my_mutex mutex;
void error(int err, char *msg);
void test_function(void *arg);

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr,"error : wrong number of arguments.\n");
    return EXIT_FAILURE;
  }
  int nb_threads = atoi(argv[1]);
  if(nb_threads < 1){
    fprintf(stderr,"error : wrong number of threads.\n");
    return EXIT_FAILURE;
  }

  srand(time(NULL));
  int i;
  int err;
  int zero = 0;
  int un = 1;
  my_mutex_init(&mutex);
  pthread_t threads[nb_threads];
  
  for(i=0; i < nb_threads; i++){
    if(i == zero)
      err = pthread_create(&threads[i], NULL, (void *) test_function, &zero);
    else
      err = pthread_create(&threads[i], NULL, (void *) test_function, &un);
    
    if(err != 0)
      error(err, "pthread_create");
  }
  for(i=0; i < nb_threads; i++){
    err = pthread_join(threads[i], NULL);
    if(err != 0)
      error(err, "pthread_join");
  }
  return EXIT_SUCCESS;
}

void error(int err, char *msg){
  fprintf(stderr, "%s a retourné %d message d'erreur : %s\n", msg, err, strerror(errno));
  exit(EXIT_FAILURE);
}

/**
 * effectue un certain nombre de random
 */
void test_function(void *arg){
  int th = *(int *)arg;
  while(true){
    my_mutex_lock(&mutex);
    printf("thread %d rentre dans sa section critique\n", th);
    printf("nb_section : %d\n",nb_sections);
    if(nb_sections <= 0){
      printf("thread %d quitte sa section critique car nb_sections = 0\n", th);
      my_mutex_unlock(&mutex);
      return;
    }
    else
      nb_sections--;
    
    //while(rand() > RAND_MAX/10000);
    printf("thread %d quitte sa section critique\n\n", th);
    my_mutex_unlock(&mutex);
  }
}
