#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>


// Initialisation
#define N 8 // places dans le buffer

pthread_mutex_t mutex_buf; //mutex buffer
pthread_mutex_t mutex_nb_prod; //mutex produits fabriqués
pthread_mutex_t mutex_nb_cons; //mutex produits consommés
sem_t empty; //semaphore pour les producers (attente d'une place vide)
sem_t full; //semaphore pour les consumers (attente d'une place remplie à consommer)

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
  for(int i=0;rand() > RAND_MAX/10000;i++); //random time de production
  return i;
}

int consume(int item){
  while(rand() > RAND_MAX/10000); //random time de consommation
  return item/2;
}

void *producer(void *arg){
  int item = 2;
  while(true)
    {
      pthread_mutex_lock(&mutex_nb_prod);
      // section critique 1 : modif nb de productions restantes
      if(prod_nb <= 0){
	pthread_mutex_unlock(&mutex_nb_prod);
	break;
      }
      else
	prod_nb--;
      // end section critique 1
      pthread_mutex_unlock(&mutex_nb_prod);
      item=produce();
      sem_wait(&empty); // attente d'une place libre
      pthread_mutex_lock(&mutex_buf);
      // section critique 2 : buffer
      buffer[in] = item;
      in = (in+1)%N;
      // end section 2
      pthread_mutex_unlock(&mutex_buf);
      sem_post(&full); // il y a une place remplie en plus
    }
  return NULL;
}
void *consumer(void *arg)
{
  int item;
  while(true){
    pthread_mutex_lock(&mutex_nb_cons);
    //section critique 1 : modif nb de consommations restantes
    if(cons_nb <= 0){
      pthread_mutex_unlock(&mutex_nb_cons);
      break;
    }
    else
      cons_nb--;
    // end section 1
    pthread_mutex_unlock(&mutex_nb_cons);
    
    sem_wait(&full); // attente d'une place remplie
    pthread_mutex_lock(&mutex_buf);
    // section critique 2 : buffer
    item=buffer[out];
    out = (out+1)%N;
    // end section 2
    pthread_mutex_unlock(&mutex_buf);
    sem_post(&empty); // il y a une place libre en plus
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
  
  err = pthread_mutex_init(&mutex_buf, NULL);
  if(err != 0) error(err, "pthread_mutex_init");
  err = pthread_mutex_init(&mutex_nb_prod, NULL);
  if(err != 0) error(err, "pthread_mutex_init");
  err = pthread_mutex_init(&mutex_nb_cons, NULL);
  if(err != 0) error(err, "pthread_mutex_init");
  
  err = sem_init(&empty, 0 , N);  // buffer vide
  if(err != 0) error(err, "sem_init");
  err = sem_init(&full, 0 , 0);   // buffer vide
  if(err != 0) error(err, "sem_init");
  
  pthread_t prod[nb_producer];
  pthread_t cons[nb_consumer];
  
  for(i=0; i<nb_producer; i++){
    err = pthread_create(&prod[i], NULL, producer, NULL);
    if(err != 0)
      error(err, "pthread_create");
  }
  for(i=0; i<nb_consumer;i++){
    err = pthread_create(&cons[i], NULL, consumer, NULL);
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
  
  err = pthread_mutex_destroy(&mutex_buf);
  if(err != 0)
    error(err, "pthread_mutex_destroy"); 
  err = pthread_mutex_destroy(&mutex_nb_prod);
  if(err != 0)
    error(err, "pthread_mutex_destroy");
  err = pthread_mutex_destroy(&mutex_nb_cons);
  if(err != 0)
    error(err, "pthread_mutex_destroy");

  err = sem_destroy(&empty);
  if(err != 0)
    error(err, "sem_destroy");
  err = sem_destroy(&full);
  if(err != 0)
     error(err, "sem_destroy");
  
  return EXIT_SUCCESS;
}
