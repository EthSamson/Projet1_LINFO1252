#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "my_mutex.h"
#include "my_sem.h"

typedef struct Ids{
  int left;
  int right;
} Ids_t;

static my_mutex *baguette;

void error(int err, char *msg){
  fprintf(stderr, "%s a retourné %d message d'erreur : %s\n", msg, err, strerror(errno));
  exit(EXIT_FAILURE);
}

void mange(int id) {
}

void *philosophe(void *arg){
  Ids_t *ids = (Ids_t *) arg;
  int left = ids->left;
  int right = ids->right;
  for(int i=0; i<1000000;i++){
    if(left < right){
      my_mutex_testlock(&baguette[left]);
      my_mutex_testlock(&baguette[right]);
    }
    else{
      my_mutex_testlock(&baguette[right]);
      my_mutex_testlock(&baguette[left]);
    }
    mange(ids->left);
    my_mutex_unlock(&baguette[left]);
    my_mutex_unlock(&baguette[right]);
  }
  return (NULL);
}

/**
 * @argv[1] : nb de philosophes (min 2)
 */
int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr, "error : wrong number of args\n");
    return(EXIT_FAILURE);
  }
  int philNum = atoi(argv[1]);
  if(philNum < 2){
    fprintf(stderr, "error : not enough philosophes\n");
    return(EXIT_FAILURE);
  }
  
  baguette = malloc(philNum*sizeof(my_mutex));
  if(baguette==NULL){
    fprintf(stderr, "error malloc baguette.\n");
    return EXIT_FAILURE;
  }
  int i;
  Ids_t ids[philNum];
  int err;
  pthread_t phil[philNum];

  for(i=0; i<philNum; i++){
    ids[i].left = i;
    ids[i].right = (i+1) % philNum;
  }
  
  for(i=0; i<philNum; i++){
    my_mutex_init(&baguette[i]);
  }
  
  for(i=0; i<philNum; i++){
    err=pthread_create(&phil[i], NULL, philosophe, (void*) &(ids[i]) );
    if(err!=0)
       error(err,"pthread_create");
  }
  
  for(i=0; i<philNum; i++){
    pthread_join(phil[i], NULL);
    if(err!=0)
      error(err, "pthread_join");
  }
  
  free(baguette);
  return (EXIT_SUCCESS);
}
