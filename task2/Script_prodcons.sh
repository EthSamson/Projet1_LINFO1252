#!/bin/bash


NPROC=6
run=5

make clean
make prodconstest

echo "==PRODUCERS - CONSUMMERS=="
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/prodcons.csv

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	output=$(/usr/bin/time -f %e ./prodconstest $n $n 1024 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/prodcons.csv
    unset myArray
    echo $l" run(s) done"
done
