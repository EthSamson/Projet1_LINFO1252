#!/bin/bash

NPROC=6
run=5

make clean
make tatastest

echo "==TEST_AND_TEST_AND_SET=="
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads" > stats/tatas.csv

for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	m=$((2 * $n))
	echo $m" threads"
	output=$(/usr/bin/time -f %e ./tatastest $m 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats/tatas.csv
    unset myArray
    echo $l" run(s) done"
done
