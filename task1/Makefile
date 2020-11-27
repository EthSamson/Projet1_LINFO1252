PY3=python3

all: graph1_1 graph1_2 graph1_3

graph1_1: task1_1
	$(PY3) graph1_1.py

graph1_2: task1_2
	$(PY3) graph1_2.py

graph1_3: task1_3
	$(PY3) graph1_3.py

task1_1: task1_1.c Script1_1.sh
	./Script1_1.sh

task1_2: task1_2.c Script1_2.sh
	./Script1_2.sh

task1_3: task1_3.c Script1_3.sh
	./Script1_3.sh

clean1:
	rm -rf philo prodCons readWrite

mrproper: clean1
	rm -rf /img/*.pdf /img/*.png /stats/*.csv 
