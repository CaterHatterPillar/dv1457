
function log_sum_f()
{	
	if(httpRequest == "PUT" || httpRequest == "POST" || httpRequest == "PATCH")
	{	
		print httpRequest;
		f_results[ip] += (numBytes+0);	
	}
}

function display_f_results(limit)
{
	resSize = sortAssociativeArrayValue(f_results, res);

	if((limit+0) > (resSize+0))
		limit = resSize;
	if((limit+0) < 0)
		limit = resSize;

	print "Number of bytes sent to the server."
	print "Ip Address: \t NumBytes:"
	for(i=1; i<=(limit+0); i++)
	{
		split(res[i], values, " ")
		print values[2], "\t", values[1];
	}
	print "";
}