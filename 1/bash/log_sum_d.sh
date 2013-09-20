
function log_sum_d() {
	dateLimit=$1
	filename=$2

	linesSorted=()
	declare -A monthNumeric
	monthNumeric['Jan']="01"
	monthNumeric['Feb']="02"
	monthNumeric['Mar']="03"
	monthNumeric['Apr']="04"
	monthNumeric['May']="05"
	monthNumeric['Jun']="06"
	monthNumeric['Jul']="07"
	monthNumeric['Aug']="08"
	monthNumeric['Sep']="09"
	monthNumeric['Oct']="10"
	monthNumeric['Nov']="11"
	monthNumeric['Dec']="12"

	OLDIFS=$IFS
	IFS=$'\n'

	readarray lines < $filename
	dates=($(egrep -o '[[:digit:]]{2}/[[:alpha:]]{3}/[[:digit:]]{4}:[[:digit:]]{2}:[[:digit:]]{2}:[[:digit:]]{2} \+[[:digit:]]{4}' $filename))

	#1986-05-05_09:22:23
	lDay=${dateLimit:8:2}
	lMonth=${dateLimit:5:2}
	lYear=${dateLimit:0:4}
	lHour=${dateLimit:11:2}
	lMinute=${dateLimit:14:2}
	lSecond=${dateLimit:17:2}

	linesSorted=()
	for aDate in "${dates[@]}" ; do
		#echo $date
	 	day=${aDate:0:2}
	 	month=${aDate:3:3}
	 	month=${monthNumeric[$month]}
	 	year=${aDate:7:4}
	 	hour=${aDate:12:2}
	 	minute=${aDate:15:2}
	 	second=${aDate:18:2}
	 	timezone=${aDate:21:5} # Skip timezones due to brevity.

	 	# Trust me, I'm an engineer.
	 	if [[ 
	 		("$year" 	> "$lYear" 		|| "$year" 		= "$lYear"	) 	&& 
	 		("$month" 	> "$lMonth" 	|| "$month" 	= "$lMonth"	) 	&& 
	 		("$day" 	> "$lDay" 		|| "$day" 		= "$lDay"	) 	&& 
	 		("$hour" 	> "$lHour" 		|| "$hour" 		= "$lHour"	) 	&& 
	 		("$minute" 	> "$lMinute" 	|| "$minute" 	= "$lMinute") 	&& 
	 		("$second" 	> "$lSecond" 	|| "$second" 	= "$lSecond") ]] ; then
	 		linesSorted+=( ${lines[$i]} )
	 	fi
	done

	#for line in "${linesSorted[@]}"
	#do
	#	echo $line
	#done

	IFS=$OLDIFS
}