#!/bin/sh

#
#      nrev - Narthex reverser
#  by Michael Constantine Dimopoulos https://mcdim.xyz <mk@mcdim.xyz>
#
#  nrev iterates over stdin or a file and, after reprinting the
#  dctionary, it will reprint it again but with each line reversed.
#
###################
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.


version="1.2.1"

if   [ "$1" = "-v" ]; then echo v$version; exit;
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
