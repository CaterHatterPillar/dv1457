#! /bin/bash

source log_sum_resultCount.sh
source log_sum_result.sh

function log_sum_r() {
	OLDIFS=$IFS
	IFS=$'\n'

	log_sum_resultCount

	finalResults=($(
	for i in "${!resultCount[@]}" ; do
 		resultCode=$i
 		resultCount=${resultCount[$i]}

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
	done | sort -k12 -n -r ))

	IFS=$OLDIFS
}