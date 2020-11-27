#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "my_mutex.h"

int nb_sections = 6400;
my_mutex mutex;
void error(int err, char *msg);
void test_function(void *arg);

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr, "error : wrong number of arguments.\n");
    return EXIT_FAILURE;
  }
  int nb_threads = atoi(argv[1]);
  if(nb_threads < 1){
    fprintf(stderr,"error : wrong number of threads\n");
    return EXIT_FAILURE;
  }
  srand(time(NULL));
  int i;
  int err;
  my_mutex_init(&mutex);
  printf("state : %d\n", mutex.state);
  pthread_t threads[nb_threads];
  int t_nb[nb_threads];
  
  for(i=0; i < nb_threads; i++){
    t_nb[i] = i;
  }
  
  for(i=0; i < nb_threads; i++){
    err = pthread_create(&threads[i], NULL, (void *) test_function, &t_nb[i]);
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
  while(true){
    my_mutex_testlock(&mutex);
    if(nb_sections <= 0){
      my_mutex_unlock(&mutex);
      return;
    }
    else
      nb_sections--;
    
    while(rand() > RAND_MAX/10000);
    my_mutex_unlock(&mutex);
  }
}
