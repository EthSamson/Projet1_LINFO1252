CC=gcc
FLAGS=-lpthread -Wall -Werror

mytest: main.o my_mutex.o
	$(CC) -o mytest main.o my_mutex.o $(FLAGS)

main.o: main.c my_mutex.h
	$(CC) -c main.c $(FLAGS)

my_mutex.o: my_mutex.c my_mutex.h
	$(CC) -c my_mutex.c $(FLAGS)

clean:
	rm -rf *.o mytest
