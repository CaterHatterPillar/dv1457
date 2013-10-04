
function calcTimeLimit(hLimit, dLimit)
{
	format = "%Y %m %d %H %M %S";
	curTime = strftime(format);

	split(curTime, components, " ");

	components[3] = components[3] - dLimit;
	if(length(components[3]) == 1)
		components[3] = sprintf("0%s", components[3]);

	components[4] = components[4] - hLimit;
	if(length(components[4]) == 1)
		components[4] = sprintf("0%s", components[4]);
	
	timeLimit=sprintf("%s %s %s %s %s %s", components[1], components[2], components[3],
		components[4], components[5], components[6]);

	return mktime(timeLimit);
}