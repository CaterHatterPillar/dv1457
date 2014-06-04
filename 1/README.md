
We are aware that log_sum.sh has a very long execution time. This is due to the function date that we use to compare the date specified by the user to the dates in the file. We tried to do a work around by converting the strings representing year, month, day, hour, minute and second to numeric values and compare them to the limits specified by the user individually but it turned out that converting the strings to numeric values was about as slow as using date. We also tried comparing the strings directly but was unable to produce correct results.

As we understand awk parameters can't be passed to the script in the same way as bash. Instead variables are specified. Therefore the flag -2 could not be used. Instead this was switch to s. To be able to include files in awk we have used an extension of GNU awk called igawk. Following is an example of calling our awk program:

	igawk -f log_sum.awk n=10 d=10000 h=3 s=1 c=1 t=1 thttpd.log

We were unsure how the flag -f was supposed to be implemented since the number of bytes sent from the client to server is not specified in the log-file. Both the instructions provided for the assignment and the documentation at: http://httpd.apache.org/docs/1.3/logs.html states that the field representing number of bytes is the amount that was sent to the client.
So we chose to look at the http request to determine which way the data would be traveling, i.e the result codes "PUT", "POST", "PATCH" would indicate the client sending data to the server, otherwise the client recieves data. 

Please use python 3.4 or above to run the .py-scripts. 