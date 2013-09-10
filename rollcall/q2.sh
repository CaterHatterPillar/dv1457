#! /bin/bash

if [ "$#" -ne 3 ]
then
	echo "More or less arguments than three have been supplied."
	exit 1
fi

array=( "$@" )
IFS=$'\n'
echo "${array[*]}" | sort -nr | head -n1

#add=$(expr $1 + $2)
#echo "Result: $add"

exit 0
