
function log_sum_d() {
	dateLimit=$1
	filename=$2

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

	OLDIFS=$IFS
	IFS=$'\n'

	readarray lines < $filename
	dates=($(egrep -o '[[:digit:]]{2}/[[:alpha:]]{3}/[[:digit:]]{4}:[[:digit:]]{2}:[[:digit:]]{2}:[[:digit:]]{2} \+[[:digit:]]{4}' $filename))

	echo ${#dates[@]}

	linesSorted=()
	i=0
	for date in "${dates[@]}" ; do
		#echo $date
	 	day=${date:0:2}
	 	month=${date:3:3}
	 	month=${monthNumeric[$month]}
	 	year=${date:7:4}
	 	hour=${date:12:2}
	 	minute=${date:15:2}
	 	second=${date:18:2}
	 	timezone=${date:21:5}
	 	dateDelta=$(date --date="$year$month$day $hour:$minute:$second" +%s)
	
	 	#if [ $dateDelta -gt $dateLimit ] ; then
	 	#	#linesSorted[$[${#linesSorted[@]}+1]]=${lines[$i]}
	 	#	linesSorted+=( ${lines[$i]} )
	 	#fi

		#i=$(expr $i + 1)
	done

	#for line in "${linesSorted[@]}"
	#do
	#	echo $line
	#done

	IFS=$OLDIFS
}