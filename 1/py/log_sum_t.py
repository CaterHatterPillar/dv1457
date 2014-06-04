#! /usr/bin/python -tt

import re
import sys

import log_sum_const
from log_sum_const import *

def log_sum_t( src, results ):
	ipToCount = {}
	for line in src:
		mo = re.search( filterBytesSent, line )
		if mo:
			mo = re.search( "[0-9]{1,}$", mo.string[ mo.start(0):mo.end(0) ] )
			numBytes = mo.string[ mo.start(0):mo.end(0) ]
			
			mo = re.search( filterIP, line )
			ip = mo.string[ mo.start(0):mo.end(0) ]

			if ip in ipToCount:
				ipToCount[ip] = ipToCount[ip] + int(numBytes)
			else:
				ipToCount[ip] = int(numBytes)

	for ip in sorted( ipToCount, key = ipToCount.get, reverse = True ):
		results.append( ip + "\t" + str(ipToCount[ip]) )