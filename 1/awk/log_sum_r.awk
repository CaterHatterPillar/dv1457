
r_results[0]=0;

function log_sum_r()
{
	r_results[sprintf("%s %s", ip, statusCode)]++;
}

function display_r_results(limit)
{
	num = sortAssociativeArrayValue(r_results, tmp)
	num = findUniqueCodes(tmp, num, res);

	for(i=1; i<=num; i++)
		print res[i];
}

function findUniqueCodes(source, sourceSize, res)
{
	resSize=1;
	res[resSize] = source[1];
	for(sourceIdx=1; sourceIdx<=sourceSize; sourceIdx++)
	{
		split(source[sourceIdx], sourceSplit, " ");
		
		codeFound=0;
		for(resIdx=1; resIdx<=resSize; resIdx++)
		{
			split(res[resIdx], resSplit, " ");
			if(resSplit[3] == sourceSplit[3])
				codeFound = 1;
		}
		if(codeFound == 0)
		{
			resSize++;
			res[resSize] = source[sourceIdx];
		}
	}
	return resSize;
}