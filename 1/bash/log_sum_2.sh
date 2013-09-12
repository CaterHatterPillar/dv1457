#! /bin/bash

#
#Layout of log file:
#ip-adress, ident-answer, username, date and time, request line, http status code, num bytes, referrer page, user agent string
#
#

source log_sum_d.sh

function log_sum_2() {

	for d_line in "${linesSorted[@]}"
	do
		local ips=$(echo $d_line | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}' )
		local statusCodes=$(echo $d_line | egrep -o ' [[:digit:]]{3} ' )
	
	done

#	index=0
#	while [ $index -lt ${#ips[@]} ]
#	do
#		echo "ip: ${ips[@]}"
#		echo "StatusCode: ${statusCodes[$index]}"
#		index=$(expr $index + 1)
#	done


}
