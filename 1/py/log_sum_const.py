#! /usr/bin/python -tt

# Date format: 31/Mar/2002:19:50:45 +0200
filterDate = "[0-9]{2}/[a-zA-Z]{3}/[0-9]{4}:[0-9]{2}:[0-9]{2}:[0-9]{2} \+[0-9]{4}"

# IP format: 172.16.0.3
filterIP = "[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}"

# Result format: HTTP/1.0" 404
filterResult = "[0-9]{3}"
filterResultExt = "HTTP/[0-9]{1}\.[0-9]{1}\" [0-9]{3}"