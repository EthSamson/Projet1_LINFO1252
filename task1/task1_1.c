#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct Ids{
  int left;
  int right;
} Ids_t;

static pthread_mutex_t *baguette;

void error(int err, char *msg){
  fprintf(stderr, "%s a retourné %d message d'erreur : %s\n", msg, err, strerror(errno));
  exit(EXIT_FAILURE);
}

void mange(int id) {
  //printf("Philosophe [%d] mange\n",id);
}

void *philosophe(void *arg){
  Ids_t *ids = (Ids_t *) arg;
  int left = ids->left;
  int right = ids->right;
  for(int i=0; i<1000000;i++){
    if(left < right){
      pthread_mutex_lock(&baguette[left]);
      pthread_mutex_lock(&baguette[right]);
    }
    else{
      pthread_mutex_lock(&baguette[right]);
      pthread_mutex_lock(&baguette[left]);
    }
    mange(ids->left);
    pthread_mutex_unlock(&baguette[left]);
    pthread_mutex_unlock(&baguette[right]);
  }
  //printf("Philosophe [%d] a fini\n",left);
  return (NULL);
}

/**
 * arg1 : nb de philosophes (min 2)
 */
int main(int argc, char *argv[]){
  int philNum = atoi(argv[1]);
  if(argc != 2){
    fprintf(stderr, "error : wrong number of args\n");
    return(EXIT_FAILURE);
  }
  if(philNum < 2){
    fprintf(stderr, "error : not enough philosophes\n");
    return(EXIT_FAILURE);
  }
  
  baguette = malloc(philNum*sizeof(pthread_mutex_t));
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
    err=pthread_mutex_init(&baguette[i],NULL);
    if(err!=0)
      error(err, "pthread_mutex_init");
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

  for(i=0; i<philNum; i++){
    pthread_mutex_destroy(&baguette[i]);
    if(err!=0)
      error(err,"pthread_mutex_destroy");
  }
  
  free(baguette);
  return (EXIT_SUCCESS);
}
