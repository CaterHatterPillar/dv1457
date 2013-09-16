#! /usr/bin/python -tt

import re
import sys

import log_sum_const
from log_sum_const import *

def log_sum_c( src, results ):
	ipsCount = {}
	for line in src:
		mo = re.search( filterIP, str(line) )
		if mo:
			ip = mo.string[ mo.start(0):mo.end(0) ]
			if ip in ipsCount:
				ipsCount[ip] = ipsCount[ip] + 1
			else:
				ipsCount[ip] = 1
	for ip in ipsCount:
		print( ip + ": \t" + str(ipsCount[ip]) )


# declare -A ipsCount
# 	for lineSorted in "${linesSorted[@]}"
# 	do
# 		ip=$(echo $lineSorted | egrep -o '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3} ' )
# 		ipsCount[$ip]=$(expr ${ipsCount[$ip]} + 1)
# 	done

# 	OLDIFS=$IFS
# 	IFS=$'\n'
# 	finalResults=($(for i in "${!ipsCount[@]}" ; do
# 		ipCount=${ipsCount[$i]}
# 	 	ip=$i

# 	 	echo -e "$ip \t $ipCount"
# 	done | sort -k2 -n -r))
# 	IFS=$OLDIFS