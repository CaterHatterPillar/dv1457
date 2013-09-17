
@include log_sum_data.awk

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

function sortAssociativeArrayValue(source, dest)
{
	dest[1]="0 0.0.0.0";
	destSize=1;
	for(idx in source)
	{
		for(destIdx=1; destIdx<=destSize; destIdx++)
		{
			split(dest[destIdx], values, " ")
			if((source[idx]+0) >= (values[1]+0))
			{
				for(i=destSize; i>=destIdx; i--)
					dest[i+1] = dest[i];
				dest[destIdx] = sprintf("%s %s", source[idx], idx);
				break;
			}
		}
		destSize++;
	}
	return destSize;
}