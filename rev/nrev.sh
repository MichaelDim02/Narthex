#!/bin/sh

version="1.0"

if   [ "$1" = "-v" ]; then echo version; exit;
elif [ "$1" = "-h" ];
then
	printf  "Nrev - Narthex reverser ${version}  \n";
	printf	"By Michael C. Dim.  <mk@mcdim.xyz>\n\n";
	printf	'%s\n' "-h  Print this panel & exit";
	printf	'%s\n\n' "-v  Print current version & exit";
	printf	"Usage:	nrev [FILENAME]\n";
	printf  "	cat [FILENAME] | nrev\n";
	exit;
fi

filename=$(mktemp);

while read line
do
	echo "$line" >> $filename;
done < "${1:-/dev/stdin}"

cat $filename;
cat $filename | rev;
