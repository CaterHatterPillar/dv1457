#! /usr/bin/python -tt

import re
import sys

import time
import datetime

# Date format: 31/Mar/2002:19:50:45 +0200
filterDate = "[0-9]{2}/[a-zA-Z]{3}/[0-9]{4}:[0-9]{2}:[0-9]{2}:[0-9]{2} \+[0-9]{4}"

monthToInt = { 
	'Jan' : '01',
	'Feb' : '02',
	'Mar' : '03',
	'Apr' : '04',
	'May' : '05',
	'Jun' : '06',
	'Jul' : '07',
	'Aug' : '08',
	'Sep' : '09',
	'Oct' : '10',
	'Nov' : '11',
	'Dec' : '12' }

def log_sum_filter( filename, date ):
	srcFiltered=[]

	src = open( filename, 'r' ) # r for readonly?
	for line in src:
		# Filter any lines that do not contain a date (all queries should):
		mo = re.search( filterDate, line )
		if mo:
			dte = mo.string[ mo.start(0):mo.end(0) ]
			dteDay		= dte[0:0+2]
			dteMonth	= dte[3:3+3]
			dteYear		= dte[7:7+4]
			dteHour		= dte[12:12+2]
			dteMinute	= dte[15:15+2]
			dteSec		= dte[18:18+2]
			dteTimeZone	= dte[21:21+5]

			dteObj = datetime.datetime( 
				int( dteYear 				), 
				int( monthToInt[dteMonth] 	),
				int( dteDay 				),
				int( dteHour				),
				int( dteMinute				),
				int( dteSec					) ) 
			if( (dteObj - date).total_seconds() > 0 ):
				srcFiltered.append( dteObj )
	return srcFiltered