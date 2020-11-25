CC=gcc
FLAGS=-lpthread -Wall -Werror

mytest: main.o task2_1.o
	$(CC) -o mytest main.o task2_1.o $(FLAGS)

main.o: main.c task2_1.h
	$(CC) -c main.c $(FLAGS)

task2_1.o: task2_1.c task2_1.h
	$(CC) -c task2_1.c $(FLAGS)

clean:
	rm -rf *.o mytest
