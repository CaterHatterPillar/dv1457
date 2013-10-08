#! /bin/bash

OIFS=$IFS
IFS=" "
pInfo=($(ps ajx | grep '\./cave_server' | grep -v 'grep'))
if [ ${#pInfo[@]} -gt 1 ]
then
	pid=${pInfo[1]}

	if [ "$1" = "k" ]
	then	
		echo "sending SIGKILL to process: $pid"
		kill -KILL $pid
	fi
	if [ "$1" = "h" ]
	then
		echo "sending SIGHUP to process: $pid"
		kill -SIGHUP $pid 
	fi
else
	echo "No server running!"
fi
