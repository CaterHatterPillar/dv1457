#! /bin/bash

function log_sum_f() {
	
	index=0
	for line in "${linesSorted[@]}" ; do
		numBytes=$(echo $line | grep 'PUT\|POST\|PATCH' | egrep -o ' [[:digit:]]{3} [[:digit:]]{1,} ')
		numBytes=${numBytes:5:${#numBytes}-1}
	
		if [ ${#numBytes} -gt 0 ] ; then	
			ip=$(echo $line | grep $numBytes | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ')
			result="$ip \t $numBytes"
			results[$index]=$result #"$ip 	$numBytes"
			index=$(expr $index + 1)
		fi
	done

	echo -e "IP Address: \t Number of bytes:"
	for result in "${results[@]}" ; do
		echo -e $result
	done | sort -k2 -n -r | uniq
}
