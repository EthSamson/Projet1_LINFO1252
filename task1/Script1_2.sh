#!/bin/bash

# Ce que fait le script :
# 1) compile la tâche 1.2 : prod/cons
# 2) run 5x la tâche 1.2, chaque run test de 1 à 6 coeurs avec 1024 prod et 1024 conso
# 3) note les résultats dans stats/stats2.csv

NPROC=6
run=5

echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/stats2.csv

gcc -lpthread -Wall -Werror -o prodCons task1_2.c

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	output=$(/usr/bin/time -f %e ./prodCons $n $n 1024 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/stats2.csv
    unset myArray
    echo $l" run(s) done"
done

