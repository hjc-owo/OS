#!bin/bash
#First you can use grep (-n) to find the number of lines of string.
#Then you can use awk to separate the answer.

touch $3
touch mid
grep -n $2 $1 >mid
awk -F: '{print $1}' mid >$3
rm mid
