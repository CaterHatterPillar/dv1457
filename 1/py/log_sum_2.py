#! /usr/bin/python -tt

import re
import sys

import log_sum_const
from log_sum_const import *

import log_sum_c
from log_sum_c import log_sum_c

def log_sum_2( src, results ):
	srcSuccess=[]
	for line in src:
		# Filter lines based on whether or not they contain the HTTP result-code '200':
		mo = re.search( filterResultExt, line )
		mo = re.search( filterResult, mo.string[ mo.start(0):mo.end(0) ] )
		if mo.string[ mo.start(0):mo.end(0) ] == "200":
			srcSuccess.append( line )

	log_sum_c( srcSuccess, results )