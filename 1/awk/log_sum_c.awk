
function log_sum_c()
{
	c_results[ip]++;
}

function display_c_results(limit)
{
	resSize = sortAssociativeArrayValue(c_results, res)
	
	if((limit+0) > (resSize+0))
		limit = resSize;
	if((limit+0) < 0)
		limit = resSize;

	print "Number of cennection attempts."
	print "Ip Address: \t Connecion Attempts:"
	for(i=1; i<=(limit+0); i++)
	{
		split(res[i], values, " ")
		print values[2], "\t", values[1];
	}
	print "";
}
