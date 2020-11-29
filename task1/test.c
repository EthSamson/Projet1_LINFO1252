#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include <limits.h>
int main(int argc, char *argv[]){
  srand(time(NULL));
  printf("%d\n", INT_MAX);
  printf("%d\n", INT_MIN+2*rand()+1);
  return EXIT_SUCCESS;
}
