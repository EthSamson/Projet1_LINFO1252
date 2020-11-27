#!/bin/bash

# Ce que fait le script :
# 1) compile la tâche 1.3 : readers/writers
# 2) run 5x la tâche 1.3, chaque run test de 1 à 6 coeurs
# 3) note les résultats dans stats/stats3.csv

NPROC=6
run=5
gcc task1_3.c -o readWrite -lpthread -Wall -Werror

echo "==READERS - WRITERS=="
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/stats3.csv

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	output=$(/usr/bin/time -f %e ./readWrite $n $n 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/stats3.csv
    unset myArray
    echo $l" run(s) done"
done