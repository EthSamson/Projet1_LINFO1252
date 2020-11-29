CC=gcc
FLAGS=-lpthread -Wall -Werror

all: scriptPhilo scriptReadwrite scriptProdcons scriptTas scriptTatas

scriptPhilo: philotest
	./Script_philo.sh

scriptReadwrite: readwritetest
	./Script_readwrite.sh

scriptProdcons: prodconstest
	./Script_prodcons.sh

scriptTas: tastest
	./Script_tas.sh

scriptTatas: tatastest
	./Script_tatas.sh

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

.PHONY: clean

clean:
	rm -rf *.o tastest tatastest mybadtest semtest prodconstest philotest readwritetest

mrproper: clean
	rm -rf /stats/*.csv 
