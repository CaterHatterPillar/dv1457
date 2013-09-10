#! /bin/bash

if [ "$#" -ne 2 ]
then
	echo "More or less arguments than two have been supplied."
	exit 1
fi

add=$(expr $1 + $2)
echo "Result: $add"

exit 0
