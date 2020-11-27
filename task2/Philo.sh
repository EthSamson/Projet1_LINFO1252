#!/bin/bash

# Ce que fait le script :
# 1) compile la tâche 1.1 : philosophes
# 2) run 5x la tâche 1.1, chaque run test de 1 à 6 coeurs (-> 2 à 12 philosophes) avec 1.000.000 cycles/philosophe
# 3) note les résultats dans stats/stats1.csv

NPROC=6
run=5

make clean
make philotest

echo "==PHILOSOPHES=="
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/stats1.csv

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	m=$((2 * $n))
	output=$(/usr/bin/time -f %e ./philo $m 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/stats1.csv
    unset myArray
    echo $l" run(s) done"
done
