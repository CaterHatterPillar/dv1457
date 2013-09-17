
function log_read() {
	OLDIFS=$IFS
	IFS=$'\n'
	lines=($(grep '' thttpd.log))	
	IFS=$OLDIFS
}

function log_sort_dates() {
	dateLimit=$1

	linesSorted=()
	declare -A monthNumeric
	monthNumeric['Jan']=01
	monthNumeric['Feb']=02
	monthNumeric['Mar']=03
	monthNumeric['Apr']=04
	monthNumeric['May']=05
	monthNumeric['Jun']=06
	monthNumeric['Jul']=07
	monthNumeric['Aug']=08
	monthNumeric['Sep']=09
	monthNumeric['Oct']=10
	monthNumeric['Nov']=11
	monthNumeric['Dec']=12

	for line in "${lines[@]}"
	do
		date=$(echo $line | egrep -o '[[:digit:]]{2}/[[:alpha:]]{3}/[[:digit:]]{4}:[[:digit:]]{2}:[[:digit:]]{2}:[[:digit:]]{2} \+[[:digit:]]{4}' )

		day=${date:0:2}
		month=${date:3:3}
		month=${monthNumeric[$month]}
		year=${date:7:4}
		hour=${date:12:2}
		minute=${date:15:2}
		second=${date:18:2}
		timezone=${date:21:5}
		dateDelta=$(date --date="$year$month$day $hour:$minute:$second" +%s)

		if [ $dateDelta -gt $dateLimit ]
		then
			linesSorted[$[${#linesSorted[@]}+1]]=$line
		fi
	done
}