#!/bin/bash

NPROC=6
run=5
make clean
make readwritetest

echo "==READERS - WRITERS=="
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/readwrite.csv

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	output=$(/usr/bin/time -f %e ./readwritetest $n $n 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/readwrite.csv
    unset myArray
    echo $l" run(s) done"
done
