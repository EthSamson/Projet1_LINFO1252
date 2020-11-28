CC=gcc
FLAGS=-lpthread -Wall -Werror

readwritetest: readwrite.o my_sem.o my_mutex.o
	$(CC) -o $@ $^ $(FLAGS)

philotest: philo.o my_mutex.o
	$(CC) -o $@ $^ $(FLAGS)

prodconstest: prodcons.o my_sem.o my_mutex.o
	$(CC) -o $@ $^ $(FLAGS)

tatastest: task2_3.o my_mutex.o
	$(CC)  -o $@ $^ $(FLAGS)

tastest: task2_1.o my_mutex.o
	$(CC) -o $@ $^  $(FLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -rf *.o tastest tatastest mybadtest semtest prodconstest philotest readwritetest
