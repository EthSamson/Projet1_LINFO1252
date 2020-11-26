#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "my_sem.h"
#include "my_mutex.h"
#include <time.h>


// Initialisation
#define N 8 // places dans le buffer

my_mutex mutex_buf; //mutex buffer
my_mutex mutex_nb_prod; //mutex produits fabriqués
my_mutex mutex_nb_cons; //mutex produits consommés
my_sem empty; //semaphore pour les producers (attente d'une place vide)
my_sem full; //semaphore pour les consumers (attente d'une place remplie à consommer)

int buffer[N];
int in = 0; //index donné aux producers
int out = 0; //index donné aux consummers
int prod_nb; //nombre de production
int cons_nb; //nombre de consommation (=nombre de production avant de commencer)

void error(int err, char *msg){
  fprintf(stderr, "%s a retourné %d message d'erreur : %s\n", msg, err, strerror(errno));
  exit(EXIT_FAILURE);
}

int produce(){
  int i=0;
  //for(i=0; i<1000000; i++); //constant time de production
  for(i=0;rand() > RAND_MAX/10000;i++); //random time de production
  return i;
}

int consume(int item){
  //for(int i=0; i<10000; i++); //constant time de consommation
  while(rand() > RAND_MAX/10000); //random time de consommation
  return item/2;
}

void *producer(void *arg){
  int item = 2;
  //int *th = (int *) arg;
  while(true)
    {
      my_mutex_testlock(&mutex_nb_prod);
      
      // section critique 1 : modif nb de productions restantes
      if(prod_nb <= 0){
	my_mutex_unlock(&mutex_nb_prod);
	printf("producing done\n");
	break;
      }
      else
	prod_nb--;
      // end section critique 1
      my_mutex_unlock(&mutex_nb_prod);
      item=produce();
      my_sem_wait(&empty); // attente d'une place libre
      my_mutex_testlock(&mutex_buf);
      // section critique 2 : buffer
      buffer[in] = item;
      in = (in+1)%N;
      // end section 2
      my_mutex_unlock(&mutex_buf);
      my_sem_post(&full); // il y a une place remplie en plus
    }
  return NULL;
}
void *consumer(void *arg)
{
  //int *th = (int *) arg;
  int item;
  while(true){
    my_mutex_testlock(&mutex_nb_cons);
    //section critique 1 : modif nb de consommations restantes
    if(cons_nb <= 0){
      my_mutex_unlock(&mutex_nb_cons);
      printf("consuming done\n");
      break;
    }
    else
      cons_nb--;
    // end section 1
    my_mutex_unlock(&mutex_nb_cons);
    
    my_sem_wait(&full); // attente d'une place remplie
    my_mutex_testlock(&mutex_buf);
    // section critique 2 : buffer
    item=buffer[out];
    out = (out+1)%N;
    // end section 2
    my_mutex_unlock(&mutex_buf);
    my_sem_post(&empty); // il y a une place libre en plus
    consume(item);
  }
  return NULL;
}
/**
 * 1er arg : nombre producer
 * 2e arg : nombre consumer
 * 3e arg : nombre produits 
 */
int main(int argc, char *argv[]){
  srand(time(NULL));
  int nb_producer = atoi(argv[1]);
  int nb_consumer = atoi(argv[2]);
  prod_nb = atoi(argv[3]);
  cons_nb = prod_nb;
  int i;
  int err;
  if(argc != 4) fprintf(stderr,"error : wrong args number");
  if(nb_producer < 1) fprintf(stderr,"error : wrong producer number");
  if(nb_consumer < 1) fprintf(stderr,"error : wrong consumer number");
  
  my_mutex_init(&mutex_buf);
  
  my_mutex_init(&mutex_nb_prod);
  
  my_mutex_init(&mutex_nb_cons);
  
  
  my_sem_init(&empty, N);  // buffer vide
  my_sem_init(&full, 0);   // buffer vide
  
  //printf("empty.current_state : %d\n", empty.current_state);
  //printf("full.current_state : %d\n", empty.current_state);
  //printf("(empty.mutex).state : %d\n", (empty.mutex).state);
  // printf("(full.mutex).state : %d\n", (full.mutex).state);
  
  pthread_t prod[nb_producer];
  pthread_t cons[nb_consumer];
  int index_prod[nb_producer];
  int index_cons[nb_consumer];
  for( i=0; i < nb_producer; i++){
    index_prod[i] = i;
  }
  for( i=0; i < nb_consumer; i++){
    index_cons[i] = i;
  }
  for(i=0; i<nb_producer; i++){
    err = pthread_create(&prod[i], NULL, producer, &index_prod[i]);
    if(err != 0)
      error(err, "pthread_create");
  }
  for(i=0; i<nb_consumer;i++){
    err = pthread_create(&cons[i], NULL, consumer, &index_cons[i]);
    if(err != 0)
      error(err, "pthread_create");
  }
  for(i=0; i<nb_producer; i++){
    err = pthread_join(prod[i], NULL);
    if(err!=0)
      error(err, "pthread_join");
  }
  for(i=0; i<nb_consumer; i++){
    err = pthread_join(cons[i], NULL);
    if(err!=0)
      error(err, "pthread_join");
  }
  
  return EXIT_SUCCESS;
}
