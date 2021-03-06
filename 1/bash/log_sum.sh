#! /bin/bash

# How to call the script:
# ---
# log_sum.sh [-n N] [-h H|-d D] [-c|-2|-r|-F|-t|-f] <filename>
# ---
# -n: Limit the number of results to N.
# -h: Limit the query to the last number of hours (< 24).
# -d: Limit the query to the last number of days (counting from midnight).
# -c: Which IP address makes the most number of connection attempts?
# -2: Which address makes the most number of successful attempts?
# -r: What are the most common results codes and where do they come from?
# -F: What are the most common result codes that indicate failure (no auth, not found etc) and where do they come from?
# -t: Which IP number get the most bytes sent to them?
# -f: Which IP number sends the most bytes to the server <filename> refers to the logfile. If '-' is given as a filename, or no filename is given, then standard input should be read. This enables the script to be used in a pipeline.

source log_sum_c.sh
source log_sum_2.sh
source log_sum_r.sh
source log_sum_F.sh
source log_sum_t.sh
source log_sum_f.sh

source log_sum_d.sh

# Establish bashtrap used to escape application in case of murderous goblins and/or psychotic mystics:
trap bashtrap INT
bashtrap() {
	echo "log_sum: Script force quit. Execution was interrupted."
}

argLimitOutput=9999999
argLimitQueryHours=0
argLimitQueryDays=0
argFilename=""

# Enumeration hack:
query=-1
query_c=0
query_2=1
query_r=2
query_F=3
query_t=4
query_f=5

# Parse parameters using getopts:
while getopts ":n:|:h:d:|:c2rFtf" opt; do
	case $opt in
		n)
			argLimitOutput=$OPTARG		;;
		h)
			argLimitQueryHours=$OPTARG	;;
		d)
			argLimitQueryDays=$OPTARG	;;
		c)
			query=query_c				;;
		2)
			query=query_2				;;
		r)
			query=query_r				;;
		F)
			query=query_F				;;
		t)
			query=query_t				;;
		f)
			query=query_f				;;
		\?)
			echo "log_sum: Invalid option: -$OPTARG." >&2 
			exit 1 ;;
	esac
done

# Parse remaining mandatory parameter (filename):
argFilename=${@:$OPTIND:1}

dateLimit=0
if [ $argLimitQueryDays -gt 0 -o $argLimitQueryHours -gt 0 ] ; then
	dateLimit=$(date --date="now -$argLimitQueryDays days -$argLimitQueryHours hours" +%s)
fi
log_sum_d $dateLimit $argFilename

# When all parameters have been passed, call the specified query:
# Consider doing some sort of check to see whether or not all required arguments have been passed.
case $query in
	query_c)
		log_sum_c
		;;
	query_2)
		log_sum_2
		;;
	query_r)
		log_sum_r
		;;
	query_F)
		log_sum_F
		;;
	query_t)
		log_sum_t
		;;
	query_f)
		log_sum_f
		;;
	\?)
		echo "log_sum: Invalid query: $query."
		exit 1 ;;
esac

# Print final results:
lineCount=0
for print in "${finalResults[@]}" ; do
	if [ $lineCount -ge $argLimitOutput ] ; then
		exit 0
	fi

	echo -e "$print"
	lineCount=$(expr $lineCount + 1)
done

exit 0
