#! /bin/bash

FILENAME=thttpd.log

grep $FILENAME | cut -d'GET' -f 2
