#! /bin/bash

source log_sum_resultCount.sh
source log_sum_result.sh

function log_sum_F() {
	OLDIFS=$IFS
	IFS=$'\n'

	log_sum_resultCount

	# Load http error codes
	httpError=( $(egrep -o '[[:digit:]]{3}' log_sum_http) )

	errorCode=5
	notErrorCode=0
	finalResults=($( 
	for i in "${!resultCount[@]}" ; do
 		resultCode=$i
 		resultCount=${resultCount[$i]}
 		isErrorCode=$notErrorCode

 		for errCode in "${httpError[@]}" ; do
			if [ $resultCode = $errCode ] ; then
				isErrorCode=$errorCode
			fi
		done

		if [ $isErrorCode = $errorCode ] ; then
			resultMax=0
			ipResponsible=0
			for i in "${!resultCountIP[@]}" ; do
				count=${resultCountIP[$i]}
	 			resultIp=$i
	 			code=$(echo "$resultIp" | cut -d' ' -f1)
				ip=$(echo "$resultIp" | cut -d' ' -f2-)
	 		
	 			if [ "$code" = "$resultCode" ] ; then
	 				if (( $count > resultMax )) ; then
	 					resultMax=$count
	 					ipResponsible=$ip
	 				fi
	 			fi
			done

			echo "Result: $resultCode occurred $resultCount times. Primarily responsible ip was $ipResponsible with $resultMax occurrences."
		fi
	done | sort -k3 -n -r | uniq))

	IFS=$OLDIFS
}
