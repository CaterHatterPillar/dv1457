
function log_sum_t()
{	
	if(httpRequest == "GET" || httpRequest == "HEAD" || httpRequest == "TRACE" ||
		httpRequest == "OPTIONS" || httpRequest == "CONNECT")
	{
		t_results[ip] += (numBytes+0);	
	}
}

function display_t_results(limit)
{
	resSize = sortAssociativeArrayValue(t_results, res);

	if((limit+0) > (resSize+0))
		limit = resSize;
	if((limit+0) < 0)
		limit = resSize;

	print "Number of bytes sent to the clients."
	print "Ip Address: \t NumBytes:"
	for(i=1; i<=(limit+0); i++)
	{
		split(res[i], values, " ")
		print values[2], "\t", values[1];
	}
	print "";
		
}