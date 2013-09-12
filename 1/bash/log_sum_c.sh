#! /bin/bash

source log_parser.sh

function log_sum_c() {
	declare -A count
	max=0

	for i in "${g_ips[@]}" ; do
		if (( ++count[$i] > max )) ; then
        	max=${count[$i]}
        	winner=$i
    	fi
	done

	echo Most number of connection attempts made by : $winner, $max times.
}
