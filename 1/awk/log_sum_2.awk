
#@include log_sum_data.awk
#@include log_sum_util.awk

two_results[0]=0;

function log_sum_2()
{ 
	if( (substr(statusCode, 1, 1)+0) == 2)
	{
		two_results[ip]++;
	}
}
function display_2_results(limit)
{
	resSize = sortAssociativeArrayValue(two_results, res)
	
	if((limit+0) > (resSize+0))
		limit = resSize;
	if((limit+0) < 0)
		limit = resSize;

	print "Number of successful conection attempts."
	print "Ip Address: \t Connection attempts:"
	for(i=1; i<=(limit+0); i++)
	{
		split(res[i], values, " ")
		print values[2], "\t", values[1];
	}
	print "";
}