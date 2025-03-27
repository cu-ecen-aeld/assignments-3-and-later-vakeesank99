#!/bin/bash

writefile=$1
writestr=$2

if [ $# -eq 0 ]
then
	echo "nothing given"
	exit 1 
fi

#last=$(echo $writefile | rev | cut -d "/" -f 1 | rev)
#dir =$(dirname $writefile  )
#echo $dir
if [ ! -f $writefile ]
then
	mkdir -p $(dirname "$writefile")
	touch $writefile
fi

echo $writestr > $writefile
