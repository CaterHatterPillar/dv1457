#! /bin/bash

#
#Layout of log file:
#ip-adress, ident-answer, username, date and time, request line, http status code, num bytes, referrer page, user agent string
#
#

source log_sum_d.sh

function log_sum_2() {

	ipIndex=0
	for line in "${linesSorted[@]}"
	do
		ip=$(echo $line | grep ' 200 ' | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}')
		if [ ${#ip} -gt 1 ]
		then
			ips[$ipIndex]=$ip
			ipIndex=$(expr $ipIndex + 1)
		fi
	done

	index=0
	while [ $index -lt ${#ips[@]} ]
	do
		echo "ip: ${ips[$index]}"
		index=$(expr $index + 1)
 	done



}
