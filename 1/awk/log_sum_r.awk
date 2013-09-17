
r_results[0]=0;

function log_sum_r()
{
	r_results[statusCode]++;
}

function display_r_results(limit)
{
	resSize = sortAssociativeArrayValue(r_results, res)
	if((limit+0) < 0)
		limit = resSize;

	print "Nr: \t Codes:"
	for(i=0; i<(limit+0); i++)
		print res[i];
}