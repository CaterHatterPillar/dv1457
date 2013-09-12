#! /bin/bash

function log_sum_r() {
	# Get all result codes along with their occurences into an associative array:
	resultCount=()
	for lineSorted in "${linesSorted[@]}"
	do
		# Retrieve the result code:
		result=$(echo $lineSorted | egrep -o 'HTTP/1.1" [[:digit:]]{3}' )
		if (( ${#result} > 0 )) ; then # If a result was found.
			# Get the responsible IP:
			ip=$(echo $lineSorted | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ' )
			
			# Get the code in and of itself:
			result=$(echo $result | egrep -o '[[:digit:]]{3}')

			# Store the number of occurences of said code:
			resultCount[$result]=$(expr ${resultCount[$result]} + 1)

			#echo $ip
		fi
	done

	# # Establish the most commonly used result code:
	# mcurc=-1
	# mcurcCount=0
	# for i in "${!resultCount[@]}" ; do
	# 	if (( ${resultCount[$i]} > $mcurcCount )) ; then
	# 		mcurcCount=${resultCount[$i]}
	# 		mcurc=$i
	# 	fi
	# done

	# echo "key  : $mcurc"
	# echo "value: $mcurcCount"

	# declare -A resultIps
	# for lineSorted in "${linesSorted[@]}" ; do
	# 	# Retrieve the result code:
	# 	result=$(echo $lineSorted | egrep -o 'HTTP/1.1" $mcurc' )
	# 	result=$(echo $result | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ')

	# 	# Store the number of occurences of said code:
	# 	#resultIps[$result]=$(expr ${resultIps[$result]} + 1)

	# 	echo $result
	# done

	#for resultIp in "${resultIps[@]}" ; do
	#	echo $resultIp
	#done
}
#HTTP/1.1" 404

# -r: What are the most common results codes and where do they come from?

#resultCodes=()
#resultCodes[$[${#resultCodes[@]}+1]]=$lineSorted