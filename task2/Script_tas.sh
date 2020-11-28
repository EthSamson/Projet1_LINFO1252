#!/bin/bash

NPROC=6
run=5

make clean
make tastest

echo "==TEST_AND_SET=="
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/tas.csv

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	m=$((2 * $n))
	output=$(/usr/bin/time -f %e ./tastest $m 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/tas.csv
    unset myArray
    echo $l" run(s) done"
done
