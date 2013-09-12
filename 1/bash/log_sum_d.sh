
function log_read() {
	OLDIFS=$IFS
	IFS=$'\n'

	lines=($(egrep '[[:digit:]]{2}/[[:alpha:]]{3}/[[:digit:]]{4}:[[:digit:]]{2}:[[:digit:]]{2}:[[:digit:]]{2} \+[[:digit:]]{4}' thttpd.log))	
	IFS=$OLDIFS
}

function log_sort_dates() {
	dateLimit=$1

	months=('Jan' 'Feb' 'Mar' 'Apr' 'May' 'Jun' 'Jul' 'Aug' 'Sep' 'Okt' 'Nov' 'Dec')
	monthsNr=(01 02 03 04 05 06 07 08 09 10 11 12)

	for line in "${lines[@]}"
	do
		date=$(echo $line | egrep -o '[[:digit:]]{2}/[[:alpha:]]{3}/[[:digit:]]{4}:[[:digit:]]{2}:[[:digit:]]{2}:[[:digit:]]{2} \+[[:digit:]]{4}' )

		day=${date:0:2}
		month=${date:3:3}
		year=${date:7:4}
		hour=${date:12:2}
		minute=${date:15:2}
		second=${date:18:2}
		timezone=${date:21:5}

		index=0
		for key in "${months[@]}"
		do
			if [ "$month" = "$key" ]
			then
				month=${monthsNr[index]}
			fi
			index=$(expr $index + 1)
		done
		
		dateDelta=$(date --date="$year$month$day $hour:$minute:$second" +%s)

		if [ $dateDelta -gt $dateLimit ]
		then
			linesSorted+=line
			echo "$line"
		fi

	done
	
	
	
}