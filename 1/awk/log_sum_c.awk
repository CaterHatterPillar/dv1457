
@include log_sum_data.awk

c_results[0]=0;

function log_sum_c()
{
	c_results[ip]++;
}

function display_c_results(limit)
{
	#tmp[1]="0 0.0.0.0";
	#tmpSize=1;
	#for(ip in c_results)
	#{
	#	for(tmpIndex=1; tmpIndex<=tmpSize; tmpIndex++)
	#	{
	#		split(tmp[tmpIndex], values, " ")
	#		if((c_results[ip]+0) >= (values[1]+0))
	#		{
	#			for(i=tmpSize; i>=tmpIndex; i--)
	#				tmp[i+1] = tmp[i];
	#			tmp[tmpIndex] = sprintf("%s %s", c_results[ip], ip);
	#			break;
	#		}
	#	}
	#	tmpSize++;
	#}

	#if((limit+0) < 0)
	#	limit = tmpSize;

	#tst(tmp, limit);

	resSize = sortAssociativeArrayValue(c_results, res)
	if((limit+0) < 0)
		limit = resSize;

	print "Ip Address: \t Connections:"
	for(i=0; i<limit; i++)
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

function tst(source, limit)
{
	print "Ip Address: \t Connections:"
	for(i=0; i<limit; i++)
		print source[i];	
}


