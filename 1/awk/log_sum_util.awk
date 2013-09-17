
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