#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "my_mutex.h"
#include "my_sem.h"

/* Init */
my_sem sem_readcount; //modif readcount
my_sem db; // accès à la db
int readcount=0; //nombre de readers
int writing_nb = 640; //nombre d'écritures
int reading_nb = 2560; //nombre de lectures
void error(int err, char *msg){
  fprintf(stderr, "%s a retourné %d message d'erreur : %s\n", msg, err, strerror(errno));
  exit(EXIT_FAILURE);
}

void write_database(){
  // while(rand() > RAND_MAX/10000);
}
void read_database(){
  //while(rand() >  RAND_MAX/10000);
}
void process_data(){
  while(rand() >  RAND_MAX/10000);
}
void prepare_data(){
  while(rand() > RAND_MAX/10000);
}
void writer(void){
  while(true){
    prepare_data();

    my_sem_wait(&db);
    //section critique -> un seul writer à la fois sans reader
    if(writing_nb <= 0){
      //printf("end writing\n");
      my_sem_post(&db);
      return;
    }
    else
      writing_nb--;
    //printf("writing_nb : %d\n", writing_nb);
    write_database();
    //fin section critique
    my_sem_post(&db);
  }
}

void reader(void){
  while(true){
    my_sem_wait(&sem_readcount);
    //section critique
    if(reading_nb <= 0){
      //printf("end reading\n");
      my_sem_post(&sem_readcount);
      return;
    }
    else
      reading_nb--;
    
    readcount++;
    //printf("reading_nb : %d\n", reading_nb);
    my_sem_post(&sem_readcount);
    
    if(readcount==1) //arrivée du 1er reader
      my_sem_wait(&db);

    read_database();

    my_sem_wait(&sem_readcount);
    //section critique
    readcount--;
    if(readcount==0) // depart du dernier reader
      my_sem_post(&db);
    my_sem_post(&sem_readcount);
    process_data();
  }
}

int main(int argc, char *argv[]){
  srand(time(NULL));
  if(argc != 3){
    fprintf(stderr,"error : wrong args number\n");
    return EXIT_FAILURE;
  }
  int nb_writers = atoi(argv[1]);
  int nb_readers = atoi(argv[2]);
  int err;
  int i;
  if(nb_writers < 1){
    fprintf(stderr,"error : wrong writers number\n");
    return EXIT_FAILURE;
  }
  if(nb_readers < 1){
    fprintf(stderr,"error : wrong readers number\n");
    return EXIT_FAILURE;
  }
  
  my_sem_init(&db, 1);

  my_sem_init(&sem_readcount, 1);

  pthread_t writers[nb_writers];
  pthread_t readers[nb_readers];

   for(i=0; i<nb_writers; i++){
     err = pthread_create(&writers[i], NULL,(void *) writer, NULL);
     if(err != 0)
       error(err, "pthread_create");
   }
   for(i=0; i<nb_readers; i++){
     err = pthread_create(&readers[i], NULL,(void *) reader, NULL);
     if(err != 0)
       error(err, "pthread_create");
   }
   
   for(i=0; i<nb_writers; i++){
     err = pthread_join(writers[i], NULL);
     if(err!=0)
       error(err, "pthread_join");
   }
   for(i=0; i<nb_readers; i++){
     err = pthread_join(readers[i], NULL);
     if(err!=0)
       error(err, "pthread_join");
   }
   
   return EXIT_SUCCESS;
}
