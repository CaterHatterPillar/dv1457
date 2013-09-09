#! /bin/bash

# How to call the script:
# ---
# log_sum(.sh|.py) [-n N] [-h H|-d D] [-c|-2|-r|-F|-t|-f] <filename>
# ---
# -n: Limit the number of results to N.
# -h: Limit the query to the last number of hours (< 24).
# -d: Limit the query to the last number of days (counting from midnight).
# -c: Which IP address makes the most number of connection attempts?
# -2: Which address makes the most number of successful attempts?
# -r: What are the most common results codes and where do they come from?
# -F: What are the most common result codes that indicate failure (no auth, not found etc) and where do they come from?
# -t: Which IP number get the most bytes sent to them?
# -f: Which IP number sends the most bytes to the server <filename> refers to the logfile. If '-' is given as a filename, or no filename is given, then standard input should be read. This enables the script to be used in a pipeline.

echo "log_sum: Script start."

# Establish bashtrap used to escape application in case of murderous goblins or psychotic mystics:
trap bashtrap INT
bashtrap()
{
    echo "log_sum: Script force quit. Execution was interrupted."
}

argLimitOutput=-1
argLimitQueryHours=-1
argLimitQueryDays=-1

# Parse parameters using getopts:
while getopts ":n:|:h:|:d:|:c|:2|:r|:F|:t|:f" opt; do
  case $opt in
    # Limit the number of results to N.
    n)
      echo "Limit the number of results to $OPTARG." >&2
      ;;
    h)
      echo "Limit the query to the last number of hours: $OPTARG." >&2
      ;;
    d)
      echo "Limit the query to the last number of days: $OPTARG" >&2
      ;;
    c)
      echo "Which IP address makes the most number of connection attempts?" >&2
      ;;
    2)
      echo "Which address makes the most number of successful attempts?" >&2
      ;;
    r)
      echo "What are the most common results codes and where do they come from?" >&2
      ;;
    F)
      echo "What are the most common result codes that indicate failure (no auth, not found etc) and where do they come from?" >&2
      ;;
    t)
      echo "Which IP number get the most bytes sent to them?" >&2
      ;;
    f)
      echo "Which IP number sends the most bytes to the server <filename> refers to the logfile. If '-' is given as a filename, or no filename is given, then standard input should be read. This enables the script to be used in a pipeline." >&2
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      ;;
  esac
done

echo "log_sum: Script end."
exit 0
