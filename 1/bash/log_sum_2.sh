#! /bin/bash

#
#Layout of log file:
#ip-adress, ident-answer, username, date and time, request line, http status code, num bytes, referrer page, user agent string
#
#

source log_sum_d.sh
source log_sum_result.sh

function log_sum_2() {

	OLDIFS=$IFS
	IFS=$'\n'

	#Find all ip-adresses that have a successfull status code.
	declare -A ips
	for line in "${linesSorted[@]}"
	do
		ip=$(echo $line | egrep 'HTTP/[[:digit:]]{1}\.[[:digit:]]{1}\" 2[[:digit:]]{2} ' | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ')
		if [ ${#ip} -gt 1 ]
		then
			ips[$ip]=$(expr ${ips[$ip]} + 1)
		fi
	done

	#Print results and send output thruogh sort to get them in numerical order.
	finalResults=($(for ip in "${!ips[@]}"
	do
		echo "IP: $ip 	Successfull attempts: ${ips[$ip]}"
	done | sort -k5 -n -r))
	#Sort by fith column in output due to a tab between $ip and Successfull.

	IFS=$OLDIFS
}
