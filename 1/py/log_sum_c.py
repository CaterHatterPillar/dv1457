#! /usr/bin/python -tt

import re
import sys
import operator

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

	# Store results
	for ip in sorted( ipsCount, key = ipsCount.get, reverse = True ):
		results.append( str(ipsCount[ip]) + "\t" + ip )