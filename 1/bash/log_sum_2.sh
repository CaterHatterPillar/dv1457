#! /bin/bash

#
#Layout of log file:
#ip-adress, ident-answer, username, date and time, request line, http status code, num bytes, referrer page, user agent string
#
#

source log_sum_d.sh

function log_sum_2() {

	#Find all ip-adresses that have a successfull status code.
	ipIndex=0
	for line in "${linesSorted[@]}"
	do
		ip=$(echo $line | grep ' 200 ' | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ')
		if [ ${#ip} -gt 1 ]
		then
			ips[$ipIndex]=$ip
			ipIndex=$(expr $ipIndex + 1)
		fi
	done

	#Count number of times each ip-adress occurs.
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

	#Print results and send output thruogh sort to get them in numerical order.
	for i in "${!ipCount[@]}"
	do
		echo "IP: $ip 	Successfull connections: ${ipCount[$i]}"
	done | sort -k5 -n -r
	#Sort by fith column in output due to a tab between $ip and Successfull.
}
