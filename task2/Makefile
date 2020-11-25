CC=gcc
FLAGS=-lpthread -Wall -Werror

mytest2: main2.o my_mutex.o my_mutex_test.o
	$(CC) -o mytest2 main2.o my_mutex.o my_mutex_test.o $(FLAGS)

mytest1: main1.o my_mutex.o
	$(CC) -o mytest1 main1.o my_mutex.o $(FLAGS)

main2.o: main2.c my_mutex.h my_mutex_test.h
	$(CC) -c main2.c $(FLAGS)

main1.o: main1.c my_mutex.h
	$(CC) -c main1.c $(FLAGS)

my_mutex.o: my_mutex.c my_mutex.h
	$(CC) -c my_mutex.c $(FLAGS)

my_mutex_test.o: my_mutex_test.c my_mutex_test.h
	$(CC) -c my_mutex_test.c $(FLAGS)
clean:
	rm -rf *.o mytest1 mytest2
