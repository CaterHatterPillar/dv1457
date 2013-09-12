#! /bin/bash

function log_sum_c() {
	for lineSorted in "${linesSorted[@]}"
	do
		ip=$(echo $lineSorted | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}' )
		ips+=$ip

		#echo $ip
	done

	declare -A ipCount
	ipMax=0
	ipWin=0
	for ip in "${ips[@]}" ; do
		if (( ++ipCount[$ip] > ipMax )) ; then
			ipMax=${ipCount[$ip]}
			ipWin=$ip
		fi

		#echo $ip
	done

	#echo "The IP sending most queries is $ipWin with $ipMax requests."
}