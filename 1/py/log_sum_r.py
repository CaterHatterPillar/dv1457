#! /usr/bin/python -tt

import re
import sys

import log_sum_const
from log_sum_const import *

def log_sum_r( src, results ):
	ipToCode={}
	codes=[]
	for line in src:
		mo = re.search( filterResultExt, str(line) ) # For each line with a result-code.
		if mo:
			# Get code:
			mo = re.search( filterResult, mo.string[ mo.start(0):mo.end(0) ] )
			code = mo.string[ mo.start(0):mo.end(0) ]
			if code not in codes:
				codes.append( code )

			# Get IP:
			mo = re.search( filterIP, str(line) )
			ip = mo.string[ mo.start(0):mo.end(0) ]

			# Collect code, it's occurrences and the responsible IP into a two-dimensional dictionary:
			codeToCount = {}
			if ip in ipToCode:
				codeToCount = ipToCode[ip]
			else:
				ipToCode[ip] = codeToCount

			if code in codeToCount:
				codeToCount[code] = codeToCount[code] + 1
			else:
				codeToCount[code] = 1

	# Establish how many times each code occurs, along with which IP recieves it the most:
	resultsSorted = {}
	for code in codes:
		codeCountMax 	= 0
		codeCountTotal 	= 0
		codeCountMaxIP	= ""
		for ip in ipToCode:
			if code in ipToCode[ip]:
				codeCountTotal += ipToCode[ip][code]
				if( ipToCode[ip][code] > codeCountMax ):
					codeCountMax = ipToCode[ip][code]
					codeCountMaxIP = ip

		result = code + ": " + str(codeCountTotal) + " (" + str(codeCountMax) + " by " + codeCountMaxIP + ")"
		resultsSorted[result] = codeCountTotal # On what basis to sort results.

	for result in sorted( resultsSorted, key = resultsSorted.get, reverse = True ):
		results.append( result )