gcc -Wall $1 -o test > warning.txt
grep "warning" warning.txt | sed "s/warning: //g" > result.txt


if [$? -eq 0] then 
i=1
while [$i -le n]
do
test $i >> result.txt
i=$[$i+1]
done
fi

pwd -name find_warnings.sh >> result.txt

