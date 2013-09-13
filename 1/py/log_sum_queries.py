#! /usr/bin/python -tt

class Queries(Enum):
	Queries_NA = 0
	Queries_c = 1 # -c: Which IP address makes the most number of connection attempts?
	Queries_2 = 2 # -2: Which address makes the most number of successful attempts?
	Queries_r = 3 # -r: What are the most common results codes and where do they come from?
	Queries_F = 4 # -F: What are the most common result codes that indicate failure (no auth, not found etc) and where do they come from?
	Queries_t = 5 # -t: Which IP number get the most bytes sent to them?
	Queries_f = 6 # -f: Which IP number sends the most bytes to the server <filename> refers to the logfile. If '-' is given as a filename, or no filename is given, then standard input should be read. This enables the script to be used in a pipeline.