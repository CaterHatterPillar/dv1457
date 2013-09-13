#! /usr/bin/python -tt

import getopt, sys

import main
from main import *

import log_sum_queries
from log_sum_queries import Queries

# How to call the script:
# ---
# log_sum(.sh|.py) [-n N] [-h H|-d D] [-c|-2|-r|-F|-t|-f] <filename>
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


# Parse arguments using getopt:
try:
	opts, args = getopt.getopt( sys.argv[1:], ":n:|:h:d:|:c2rFtf" )
except getopt.GetoptError as err:
	print(err) # will print something like "option -a not recognized"
	sys.exit(2)

q = Queries.Queries_NA

# Interpret arguments parsed to script:
for opt, arg in opts:
	if opt == "-n":
		print("log_sum: Arglimit")
	if opt in ("-h", "-d"):
		print("log_sum: Timelimit")
	if opt in ("-c", "-2", "-r", "-F", "-t", "-f"):
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

		print("log_sum: Query")

print(q)

# Send arguments to main
main()

sys.exit(0)