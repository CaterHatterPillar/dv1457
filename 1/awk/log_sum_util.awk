
#
#Sorts the associative array source by its values,
#concatenates the value and index taken from source
#and stores it as a string in dest with a sequential index.
#
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
	#The last element is 0 0.0.0.0 that was added 
	#as a starting value for the algorithm to work.
	return destSize-1; 
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