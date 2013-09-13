#! /bin/bash

function log_sum_c() {
	ips=()
	for lineSorted in "${linesSorted[@]}"
	do
		ip=$(echo $lineSorted | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ' )
		ips[$[${#ips[@]}+1]]=$ip
	done

	for i in "${!ipsCount[@]}" ; do
		ipCount=${ipsCount[$i]}
	 	ip=$i

	 	echo -e "$ip \t $ipCount"
	done | sort -k2 -n -r
}