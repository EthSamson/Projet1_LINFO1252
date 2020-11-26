CC=gcc
FLAGS=-lpthread -Wall -Werror

prodconstest: prodcons.o my_sem.o my_mutex.o my_mutex_test.o
	$(CC) -o $@ $^ $(FLAGS)

mytest2: main2.o my_mutex.o my_mutex_test.o
	$(CC)  -o $@ $^ $(FLAGS)

mytest1: main1.o my_mutex.o
	$(CC) -o $@ $^  $(FLAGS)
%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -rf *.o mytest1 mytest2 mybadtest semtest prodconstest
