CC=gcc
FLAGS=-lpthread -Wall -Werror

readwritetest: readwrite.o my_sem.o my_mutex.o
	$(CC) -o $@ $^ $(FLAGS)

philotest: philo.o my_mutex.o
	$(CC) -o $@ $^ $(FLAGS)

prodconstest: prodcons.o my_sem.o my_mutex.o
	$(CC) -o $@ $^ $(FLAGS)

mytest2: main2.o my_mutex.o
	$(CC)  -o $@ $^ $(FLAGS)

mytest1: main1.o my_mutex.o
	$(CC) -o $@ $^  $(FLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -rf *.o mytest1 mytest2 mybadtest semtest prodconstest philotest readwritetest
