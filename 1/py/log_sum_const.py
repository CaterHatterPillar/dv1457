#! /usr/bin/python -tt

# Date format: 31/Mar/2002:19:50:45 +0200
filterDate = "[0-9]{2}/[a-zA-Z]{3}/[0-9]{4}:[0-9]{2}:[0-9]{2}:[0-9]{2} \+[0-9]{4}"

# IP format: 172.16.0.3
filterIP = "[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}"

# Result format: HTTP/1.0" 404
filterResult = "[0-9]{3}"
filterResultExt = "HTTP/[0-9]{1}\.[0-9]{1}\" [0-9]{3}"

# Nr of bytes sent format: HTTP/1.1" 200 2936
filterBytesSent = " [0-9]{3} [0-9]{1,}"

# HTTP Query format: "GET 
filterHttpQuery = "GET|HEAD|PUT|POST|DELETE|LINK|UNLINK"

httpQueries = [
	"GET", 		# Request to read a Web page
	"HEAD", 	# Request to read a Web page
	"PUT", 		# Request to write a Web page
	"POST", 	# Append to a named resource (e.g. a Web page)
	"DELETE", 	# Remove the Web page
	"LINK", 	# Connects two existing resources
	"UNLINK" ]

httpError = [
	# HTTP ERROR CLIENT
	400,
	401,
	402,
	403,
	404,
	405,
	406,
	407,
	408,
	409,
	410,
	411,
	412,
	413,
	414,
	415,
	416,
	417,
	418,
	419,
	420,
	420,
	422,
	423,
	424,
	424,
	425,
	426,
	428,
	429,
	431,
	444,
	449,
	450,
	451,
	451,
	494,
	495,
	496,
	497,
	499,

	# HTTP ERROR SERVER
	500,
	501,
	502,
	503,
	504,
	505,
	506,
	507,
	508,
	509,
	510,
	511,
	598,
	599 ]