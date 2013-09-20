
@include log_sum_c.awk
@include log_sum_2.awk
@include log_sum_r.awk
@include log_sum_F.awk
@include log_sum_t.awk
@include log_sum_f.awk
@include log_sum_data.awk
@include log_sum_time.awk
@include log_sum_util.awk

BEGIN {

	displayLimit=-1;
	dayLimit=0;
	hourLimit=0;

	arg_c = 0; #Which ip address makes the most number of connection attempts? 
	arg_2 = 0; #Which ip address makes the most number of successful attempts?
	arg_r = 0; #What are the most common result codes and where do they come from?
	arg_F = 0; #What are the most common result codes that indicate failure and where do they come from?
	arg_t = 0; #Which ip address gets the most number of bytes sent to them?
	arg_f = 0; #Which ip adress sends the most number of bytes to the server?

	for(i=0; i<ARGC; i++)
	{
		if( extractArgId(ARGV[i]) == "n")
			displayLimit = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "d")
			dayLimit = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "h")
			hourLimit = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "c")
			arg_c = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "s")
			arg_2 = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "r")
			arg_r = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "F")
			arg_F = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "t")
			arg_t = extractArgValue(ARGV[i]);
		else if( extractArgId(ARGV[i]) == "f")
			arg_f = extractArgValue(ARGV[i]);
	}
	if(dayLimit > 0 || hourLimit > 0)
		timeLimit = calcTimeLimit(hourLimit, dayLimit);
	else
		timeLimit = 0;
}
{
	extractData();

	if(time > timeLimit)
	{	
		if(arg_c > 0)
			log_sum_c();
		if(arg_2 > 0)
			log_sum_2();
		if(arg_r > 0)
			log_sum_r();
		if(arg_F > 0)
			log_sum_F();
		if(arg_t > 0)
			log_sum_t();
		if(arg_f > 0)
			log_sum_f();
	}
}
END {
	if(arg_c > 0)
		display_c_results(displayLimit);
	if(arg_2 > 0)
		display_2_results(displayLimit);
	if(arg_r > 0)
		display_r_results(displayLimit);
	if(arg_F > 0)
		display_F_results(displayLimit);
	if(arg_t > 0)
		display_t_results(displayLimit);
	if(arg_f > 0)
		display_f_results(displayLimit);

	exit 0;
}

function extractArgId(argStr)
{	
	argId = "-"
	if(substr(argStr, 2, 1) == "=")
	argId = substr(argStr, 1, 1); 

	return argId;
}
function extractArgValue(argStr)
{
	return substr(argStr, 3, length(argStr))
}