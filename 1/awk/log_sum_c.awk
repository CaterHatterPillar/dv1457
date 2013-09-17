
@include log_sum_data.awk
@include log_sum_util.awk

c_results[0]=0;

function log_sum_c()
{
	c_results[ip]++;
}

function display_c_results(limit)
{
	resSize = sortAssociativeArrayValue(c_results, res)
	if((limit+0) < 0)
		limit = resSize;

	print "Connections: \t Ip Address:"
	for(i=0; i<(limit+0); i++)
		print res[i];
}
