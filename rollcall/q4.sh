#! /bin/bash

numStars=1
for index in 1 2 3 4 5 6 7 8 9 10
do
i=0
	while [ $i -lt $numStars ]
	do
		echo -n "* "
		i=$(expr $i + 1)
	done
	echo -e "\n"
	if [ $index -lt 5 ]
	then
		numStars=$(expr $numStars + 1)
	elif [ $index -eq 5 ]
	then
		numStars=5
	else
		numStars=$(expr $numStars - 1)
	fi 
done
