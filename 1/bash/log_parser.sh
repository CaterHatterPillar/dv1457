#! /bin/bash
#	
#Parses the file thttpd.log and stores its data in a collection of arrays.
#
#


g_charIndex=0
g_ip="Unknown"
g_identAnswer="Unknown"
g_username="Unknown"
g_dateTime="Unknown"
g_requestLine="Unknown"
g_statusCode="Unknown"
g_numBytes="Unknown"
g_referrerPage="Unknown"
g_userAgent="Unknown"

function findIP() {
	local line=$1

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = " " ]
		then
			g_ip=${line:0:$g_charIndex}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done
}

function findIdentAnswer() {
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = " " ]
		then
			local length=$(expr $g_charIndex - $start)
			g_identAnswer=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done	
}

function findUsername() {
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = " " ]
		then
			local length=$(expr $g_charIndex - $start)
			g_username=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done
}

function findDateTime() {
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = "]" ]
		then
			#increment g_charIndex so the closing bracket is included.
			g_charIndex=$(expr $g_charIndex + 1)
			local length=$(expr $g_charIndex - $start)
			g_dateTime=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done	
}

function findRequestLine(){
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	#skip first qoute.
	g_charIndex=$(expr $g_charIndex + 1)

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = "\"" ]
		then
			#increment g_charIndex so the closing qoute is included.
			g_charIndex=$(expr $g_charIndex + 1)
			local length=$(expr $g_charIndex - $start)
			g_requestLine=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done	
}

function findStatusCode() {
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = " " ]
		then
			local length=$(expr $g_charIndex - $start)
			g_statusCode=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done
}

function findNumBytes() {
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = " " ]
		then
			local length=$(expr $g_charIndex - $start)
			g_numBytes=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done	
}

function findReferrerPage() {
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	#skip first qoute.
	g_charIndex=$(expr $g_charIndex + 1)

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = "\"" ]
		then
			#increment g_charIndex so the closing qoute is included.
			g_charIndex=$(expr $g_charIndex + 1)
			local length=$(expr $g_charIndex - $start)
			g_referrerPage=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done
}
function findUserAgent() {
	local line=$1

	#g_charIndex is currently at space char. 
	g_charIndex=$(expr $g_charIndex + 1)

	local start=$g_charIndex

	#skip first qoute.
	g_charIndex=$(expr $g_charIndex + 1)

	while [ $g_charIndex -lt ${#line} ]
	do
		if [ "${line:$g_charIndex:1}" = "\"" ]
		then
			#increment g_charIndex so the closing qoute is included.
			g_charIndex=$(expr $g_charIndex + 1)
			local length=$(expr $g_charIndex - $start)
			g_userAgent=${line:$start:$length}
			break
		fi
		g_charIndex=$(expr $g_charIndex + 1)
	done	
}

function parseLogFile() {
	local index=0
	while read line
	do
		g_charIndex=0
		findIP "$line"
		findIdentAnswer "$line"
		findUsername "$line"
		findDateTime "$line"
		findRequestLine "$line"
		findStatusCode "$line"
		findNumBytes "$line"
		findReferrerPage "$line"
		findUserAgent "$line"

		g_ips[$index]=$g_ip
		g_identAnswers[$index]=$g_identAnswer
		g_usernames[$index]=$g_usernames
		g_datesTimes[$index]=$g_dateTime
		g_requestLines[$index]=$g_requestLine
		g_statusCodes[$index]=$g_statusCode
		g_byteCounts[$index]=$g_numBytes
		g_referrerPages[$index]=$g_referrerPage
		g_userAgents[$index]=$g_userAgent

		echo -e -n "."
		index=$(expr $index + 1)
	done < thttpd.log
}

