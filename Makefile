PY3=python3
DIR1 = task1
DIR2 = task2
TFLAGS=-lpthread -Wall -Werror


all: graph1_1 graph1_2 graph1_3

graph1_1: task1_1
	cd $(DIR1) && $(PY3) graph1_1.py

graph1_2: task1_2
	cd $(DIR1) && $(PY3) graph1_2.py

graph1_3: task1_3
	cd $(DIR1) && $(PY3) graph1_3.py

task1_1: $(DIR1)/task1_1.c $(DIR1)/Script1_1.sh
	cd $(DIR1) && ./Script1_1.sh

task1_2: task1/task1_2.c task1/Script1_2.sh
	cd $(DIR1) && ./Script1_2.sh

task1_3: task1/task1_3.c task1/Script1_3.sh
	cd $(DIR1) && ./Script1_3.sh

clean1:
	rm -rf $(DIR1)/philo $(DIR1)/prodCons $(DIR1)/readWrite

mrproper: clean1
	rm -rf $(DIR1)/img/*.pdf $(DIR1)/img/*.png $(DIR1)/stats/*.csv 
