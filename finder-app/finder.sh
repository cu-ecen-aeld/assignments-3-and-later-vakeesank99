#!/bin/sh

filesdir=$1
searchstr=$2
if [ $# -eq 0 ]
then
	echo "no parameters given"
	exit 1
fi

if [ ! -d $filesdir ]
then
	echo "directory does not exist"
	exit 1
fi

nofiles=$(find $filesdir -type f | wc -l )
#echo $nofiles
noline=$(find $filesdir -type f -exec grep -i "$searchstr" {} + | wc -l)
#echo $noline
echo "The number of files are $nofiles and the number of matching lines are $noline"
