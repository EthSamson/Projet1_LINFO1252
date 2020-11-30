PY3=python3

all: task1_1.sh task1_2.sh task1_3.sh

task1_1: task1_1.c Script1_1.sh
	@./Script1_1.sh

task1_2: task1_2.c Script1_2.sh
	@./Script1_2.sh

task1_3: task1_3.c Script1_3.sh
	@./Script1_3.sh

.PHONY: clean

clean:
	@rm -rf philo prodCons readWrite

mrproper: clean
	@rm -rf /stats/*.csv 