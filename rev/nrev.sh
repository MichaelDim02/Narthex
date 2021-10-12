#!/bin/sh

#      nrev - Narthex reverser
#  by Michael Constantine Dimopoulos
#  https://mcdim.xyz  <mk@mcdim.xyz>
#
#  nrev iterates over stdin or a file
#  and, after reprinting the diction-
#  ary, it will reprint it again but
#  with each line reversed.

version="1.1"

if   [ "$1" = "-v" ]; then echo version; exit;
elif [ "$1" = "-h" ];
then
	printf  "nrev - Narthex reverser ${version}  \n";
	printf	"By Michael Constantine Dimopoulos <mk@mcdim.xyz>\n\n";

	printf	'%s\n' "-h  print this panel & exit";
	printf	'%s\n\n' "-v  print current version & exit";

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
