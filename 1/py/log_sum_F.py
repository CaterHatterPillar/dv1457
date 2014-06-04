#! /usr/bin/python -tt

import re
import sys

import log_sum_const
from log_sum_const import *

import log_sum_r
from log_sum_r import log_sum_r

def log_sum_F( src, results ):
	# Filter src so that the lines being sent to log_sum_r are only the ones indicating errors:
	srcError = []
	for line in src:
		mo = re.search( filterResultExt, line )
		if mo:
			mo = re.search( filterResult, mo.string[ mo.start(0):mo.end(0) ] )
			code = mo.string[ mo.start(0):mo.end(0) ]
			if int(code) in httpError:
				srcError.append( line )

	log_sum_r( srcError, results )