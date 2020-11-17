#!/bin/bash

NPROC=8
run=5
gcc -lpthread -Wall -Werror -o test task1_2.c
echo "numTentative,one_thread,two_threads,three_threads,four_threads,five_threads,six_threads,seven_threads,eight_threads" > stats2.csv
for((l=1;l<=run;l++))
do
    declare -a myArray
    for((n=1;n<=NPROC;n++))
    do
	output=$(/usr/bin/time -f %e ./test $n $n 1024 2>&1)
	myArray+=($output)
    done
    echo $l,${myArray[*]} | tr ' ' ',' >> stats2.csv
    unset myArray
    echo $l,run,done | tr ',' ' '
done

