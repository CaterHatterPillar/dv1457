#! /bin/bash

function log_sum_c() {
	ips=()
	for lineSorted in "${linesSorted[@]}"
	do
		ip=$(echo $lineSorted | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ' )
		ips[$[${#ips[@]}+1]]=$ip
	done

	declare -A ipCount
	ipMax=0
	ipWin=0
	for ip in "${ips[@]}" ; do
		ipCount[$ip]=$(expr ${ipCount[$ip]} + 1)
		if (( ${ipCount[$ip]} > ipMax )) ; then
			ipMax=${ipCount[$ip]}
			ipWin=$ip
		fi
	done

	echo "The IP sending most queries is $ipWin with $ipMax requests."
}