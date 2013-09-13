#! /bin/bash

source log_sum_result.sh

function log_sum_c() {
	declare -A ipsCount
	for lineSorted in "${linesSorted[@]}"
	do
		ip=$(echo $lineSorted | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ' )
		ipsCount[$ip]=$(expr ${ipsCount[$ip]} + 1)
	done

	OLDIFS=$IFS
	IFS=$'\n'
	finalResults=($(for i in "${!ipsCount[@]}" ; do
		ipCount=${ipsCount[$i]}
	 	ip=$i

	 	echo -e "$ip \t $ipCount"
	done | sort -k2 -n -r))
	IFS=$OLDIFS
}