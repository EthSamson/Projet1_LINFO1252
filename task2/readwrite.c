#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "my_mutex.h"
#include "my_sem.h"

my_mutex mutex_readcount;
my_mutex mutex_writecount;

my_sem db; // accès à la db
my_sem reader_block; //bloquer les readers

int readcount=0; //nombre de readers 
int writecount=0; //nombre de writers
int writing_nb = 640; //nombre d'écritures
int reading_nb = 2560; //nombre de lectures

void error(int err, char *msg){
  fprintf(stderr, "%s a retourné %d message d'erreur : %s\n", msg, err, strerror(errno));
  exit(EXIT_FAILURE);
}

void write_database(){
}
void read_database(){
}
void process_data(){
  while(rand() > RAND_MAX/10000);
}
void prepare_data(){
  while(rand() > RAND_MAX/10000);
}
void writer(void){
  while(true){
    prepare_data();
    
    my_mutex_testlock(&mutex_writecount);
    //section critique 1 : modif writecount et writing_nb
    if(writing_nb <= 0){
      my_mutex_unlock(&mutex_writecount);
      break;
    }
    else
      writing_nb--;
    writecount++;
    if(writecount==1)
      my_sem_wait(&reader_block);
    //end section 1
    my_mutex_unlock(&mutex_writecount);

    my_sem_wait(&db);
    //section critique 2 -> un seul writer à la fois sur db
    write_database();
    my_sem_post(&db);
    //end section 2
    my_mutex_testlock(&mutex_writecount);
    //section critique 3 : modif writecount
    writecount--;
   
    if(writecount==0)
      my_sem_post(&reader_block);
    //end section 3
    my_mutex_unlock(&mutex_writecount);
  }
}

void reader(void){
  while(true){
    my_sem_wait(&reader_block);//vérifie si un writer ne bloque pas la lecture
    my_mutex_testlock(&mutex_readcount);
    //section critique 1 : modif readcount et reading_nb
    if(reading_nb <= 0){
      my_mutex_unlock(&mutex_readcount);
      my_sem_post(&reader_block);
      break;
    }
    else
      reading_nb--;
    readcount++;
    if(readcount==1) //arrivée du 1er reader
      my_sem_wait(&db);
    //end section 1
    my_mutex_unlock(&mutex_readcount);
    my_sem_post(&reader_block);
    read_database();
    my_mutex_testlock(&mutex_readcount);
    //section critique 2 : modif readcount
    readcount--;
    if(readcount==0) // depart du dernier reader
      my_sem_post(&db);
    //end section 2
    my_mutex_unlock(&mutex_readcount);
    
    process_data();
  }
}

/**
 * 1er arg : nb writers
 * 2e arg : nb readers
 */
int main(int argc, char *argv[]){
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
  my_sem_init(&reader_block, 1);

  my_mutex_init(&mutex_readcount);
  my_mutex_init(&mutex_writecount);
  
  pthread_t writers[nb_writers];
  pthread_t readers[nb_readers];

   for(i=0; i<nb_writers; i++){
     err = pthread_create(&writers[i], NULL,(void *) writer, NULL);
     if(err != 0)
       error(err, "pthread_create");
   }
   for(i=0; i<nb_readers; i++){
     err = pthread_create(&readers[i], NULL, (void *)reader, NULL);
     if(err != 0)
       error(err, "pthread_create");
   }
   
   for(i=0; i<nb_writers; i++){
     pthread_join(writers[i], NULL);
     if(err!=0)
       error(err, "pthread_join");
   }
   for(i=0; i<nb_readers; i++){
     pthread_join(readers[i], NULL);
     if(err!=0)
       error(err, "pthread_join");
   }
   
   return EXIT_SUCCESS;
}
