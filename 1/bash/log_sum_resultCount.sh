#! /bin/bash

resultCount=()
declare -A resultCountIP

function log_sum_resultCount {
	# Get all the occuring result codes, along with their respective number of occurences:
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
}