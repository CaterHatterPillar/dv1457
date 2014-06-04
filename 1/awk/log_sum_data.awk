
function extractData()
{
	ip=$1;
	identAnswer=$2;
	username=$3;
	time=$4;
	timeZone=$5;
	httpRequest=$6;
	pageRequested=$7;
	httpProtocol=$8;
	statusCode=$9;
	numBytes=$10;

	time=rmFirstChar(time);
	timeZone=rmLastChar(timeZone);
	httpRequest=rmFirstChar(httpRequest);
	httpProtocol=rmLastChar(httpProtocol);

	formatDate();
}
function displayData()
{
	print "IP Address:     " ip;
	print "Ident Answer:   " identAnswer;
	print "Username:       " username;
	print "Time:           " time;
	print "Time Zone:      " timeZone;
	print "http Request:   " httpRequest;
	print "Page Requested: " pageRequested;
	print "http Protocol:  " httpProtocol;
	print "Status Code:    " statusCode;
	print "Num Bytes:      " numBytes;
	print "\n";
}

function formatDate()
{
	split(time, components, "/");
	
	day 	= components[1];
	month 	= components[2];
	
	split(components[3], components, ":")
	
	year 	= components[1];
	hour 	= components[2];
	minute 	= components[3];
	second 	= components[4]

	months[1]="Jan"; months[2]="Feb"; months[3]="Mar"; months[4]="Apr";
	months[5]="May"; months[6]="Jun"; months[7]="Jul"; months[8]="Aug";
	months[9]="Sep"; months[10]="Oct"; months[11]="Nov"; months[12]="Dec";

	monthsNr[1]="01"; monthsNr[2]="02"; monthsNr[3]="03"; monthsNr[4]="04";
	monthsNr[5]="05"; monthsNr[6]="06"; monthsNr[7]="07"; monthsNr[8]="08";
	monthsNr[9]="09"; monthsNr[10]="10"; monthsNr[11]="11"; monthsNr[12]="12";

	for(i=1; i<=12; i++)
	{
		if(month == months[i])
			month = monthsNr[i];
	}

	time = sprintf("%s %s %s %s %s %s", year, month, day, hour, minute, second);
	time = mktime(time);
}

function rmFirstChar(str)
{
	return substr(str, 2, length(str)-1);
}
function rmLastChar(str)
{
	return substr(str, 1, length(str)-1);
}