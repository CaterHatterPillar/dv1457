#! /bin/bash

function log_sum_r() {
	# Get all the occuring result codes, along with their respective number of occurences:
	resultCount=()
	declare -A resultCountIP
	for lineSorted in "${linesSorted[@]}" ; do
		# Retrieve the result code:
		result=$(echo $lineSorted | egrep -o 'HTTP/[[:digit:]]{1}.[[:digit:]]{1}" [[:digit:]]{3}' )
		if (( ${#result} > 0 )) ; then # If a result was found.
			# Get the code in and of itself:
			result=$(echo $result | egrep -o '[[:digit:]]{3}')

			# Store the number of occurences of said code:
			resultCount[$result]=$(expr ${resultCount[$result]} + 1)

			# Get the responsible IP:
			ip=$(echo $lineSorted | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ' )

			resultIP="$result $ip"
			resultCountIP[$resultIP]=$(expr ${resultCountIP[$resultIP]} + 1)
		fi
	done

	for i in "${!resultCount[@]}"
	do
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

		echo "Result: $resultCode occured $resultCount times. Primarily responsible ip was $ipResponsible with $resultMax occurrences."
	done
}