CC=gcc
PY3=python3
DIR1 = task1
TFLAGS=-lpthread -Wall -Werror


graph1_1: task1_1
	$(PY3) graph1_1.py

graph1_2: task1_2
	$(PY3) graph1_2.py

graph1_3: task1_3
	$(PY3) graph1_3.py

task1_1: task1/task1_1.c task1/Script1_1.sh
	cd $(DIR1) && ./Script1_1.sh

task1_2: task1_2.c Script1_2.sh
	cd $(DIR1) && ./Script1_2.sh

task1_3: task1_3.c Script1_3.sh
	cd $(DIR1) && ./Script1_3.sh

.PHONY: clean

clean:
	rm -rf *.o philo prodCons readWrite

mrproper: clean
	rm -rf img/*.pdf img/*.png stats/*.csv 
