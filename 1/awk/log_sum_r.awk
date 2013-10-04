

function log_sum_r()
{
	r_results[sprintf("%s %s", ip, statusCode)]++;
}

function display_r_results(limit)
{
	num = sortAssociativeArrayValue(r_results, tmp)
	num = findUniqueCodes(tmp, num, res);

	if(limit+0 > (num+0))
		limit = num;
	if((limit+0) < 0)
		limit = num;

	print "Most common result codes and ip address where they occured the most."
	print "Ip Address: \t Status Code:"
	for(i=1; i<=(limit+0); i++)
	{
		split(res[i], values, " ")
		print values[2], "\t", values[3];
	}
	print "";
}