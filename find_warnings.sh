gcc -Wall $1 -o test 2> warning.txt
grep "warning" warning.txt | sed "s/warning: //g" > result.txt

if [ $? -eq 0 ]
then 
	i=1
	while [ $i -le $2 ]
	do
		echo $i | ./test >> result.txt
		i=$[$i+1]
	done
fi

pwd find_warnings.sh >> result.txt

