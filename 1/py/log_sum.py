#! /usr/bin/python -tt

# How to call the script:
# ---
# python3 log_sum.py [-n N] [-h H|-d D] [-c|-2|-r|-F|-t|-f] <filename>
# Use Python 3.4 or above.
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

import sys
import getopt

import time
import datetime

import log_sum_filter
from log_sum_filter import *

# Queries:
import log_sum_queries
from log_sum_queries import Queries
import log_sum_c
from log_sum_c import log_sum_c
import log_sum_2
from log_sum_2 import log_sum_2
import log_sum_r
from log_sum_r import log_sum_r
import log_sum_F
from log_sum_F import log_sum_F
import log_sum_t
from log_sum_t import log_sum_t
import log_sum_f
from log_sum_f import log_sum_f

# Parse arguments using getopt:
try:
	opts, args = getopt.getopt( sys.argv[1:], ":n:|:h:d:|:c2rFtf" )
except getopt.GetoptError as e:
	print( e )
	sys.exit( 2 )

q = Queries.Queries_NA
date = datetime.datetime.now()
printLimit = sys.maxsize
filename = ""

# Interpret arguments parsed to script:
for opt, arg in opts:
	if opt == "-n":
		printLimit = int( arg )
	if opt in ( "-h", "-d" ):
		if opt == "-h": # Now - Hours
			date = date + datetime.timedelta( hours = -int(arg) )
		elif opt == "-d": # Now - Days
			date = date + datetime.timedelta( days = -int(arg) )
	if opt in ( "-c", "-2", "-r", "-F", "-t", "-f" ):
		if opt == "-c":
			q = Queries.Queries_c
		elif opt == "-2":
			q = Queries.Queries_2
		elif opt == "-r":
			q = Queries.Queries_r
		elif opt == "-F":
			q = Queries.Queries_F
		elif opt == "-t":
			q = Queries.Queries_t
		elif opt == "-f":
			q = Queries.Queries_f

# Get the last argument (filename):
filename = sys.argv[-1] # HACK

# Load the specified file:
src = open( filename, 'r' ) # r for readonly?

# Filter the input according to date:
src = log_sum_filterDate( src, date )

# Call the specified query:
results=[]
if q == Queries.Queries_c:
	results.append( "Connection attempts:" )
	log_sum_c( log_sum_filterQueries( src, ["GET"] ), results )	# Allow only GET-queries.
elif q == Queries.Queries_2:
	results.append( "Connection attempts indicating success:" )
	log_sum_2( log_sum_filterQueries( src, ["GET"] ), results )	# Allow only GET-queries.
elif q == Queries.Queries_r:
	results.append( "Common response codes:" )
	log_sum_r( log_sum_filterQueries( src, httpQueries ), results )	# Allow all HTTP-queries.
elif q == Queries.Queries_F:
	results.append( "Common response codes indicating error:" )
	log_sum_F( log_sum_filterQueries( src, httpQueries ), results )	# Allow all HTTP-queries.
elif q == Queries.Queries_t:
	results.append( "IPs recieving the highest amount of bytes:" )
	log_sum_t( log_sum_filterQueries( src, httpQueries ), results )	# Allow all HTTP-queries.
elif q == Queries.Queries_f:
	results.append( "IPs sending the highest amount of bytes:" )
	log_sum_f( log_sum_filterQueries( src, ["PUT", "POST"] ), results )	# Allow only PUT- and POST-queries.

# Print results:
i = 0
for line in results:
	if i > printLimit:
		break
	print( line )
	i += 1

sys.exit( 0 )
