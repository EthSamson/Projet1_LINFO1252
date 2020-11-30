#!/bin/bash


NPROC=6
run=5

make clean
make philotest


echo "==PHILOSOPHES=="
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/philo.csv

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	m=$((2 * $n))
	output=$(/usr/bin/time -f %e ./philotest $m 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/philo.csv
    unset myArray
    echo $l" run(s) done"
done
