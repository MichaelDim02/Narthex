#!/bin/sh

version="1.0"

printf "$(curl -s file:///home/michael/Documents/projects/c/narthex/nwiz/elder.txt)\n"

printf "NARTHEX ELDER $version\n"; sleep 0.1;
printf "Wizard program for Narthex\n"; sleep 0.1;
printf "By Michael Constantine Dimopoulos\n"; sleep 0.1;
printf "https://mcdim.xyz  <mk@mcdim.xyz>\n\n"; sleep 0.5;

printf "Leave as many empty as you like\n\n"

printf "=Questions=\n"
echo -n "Name: "
read name;  echo "$name"  >> /tmp/narthextemp.txt;
echo -n "Last name: "
read lname; echo "$lname" >> /tmp/narthextemp.txt;
echo -n "Nickname: "
read nname; echo "$nname" >> /tmp/narthextemp.txt;
echo -n "Birthday: "
read bday;  echo "$bday"  >> /tmp/narthextemp.txt;
echo -n "Birthyear: "
read byear; echo "$byear" >> /tmp/narthextemp.txt;
echo -n "Phone number: "
read phn;   echo "$phn"   >> /tmp/narthextemp.txt;
echo -n "Pet name: "
read pname; echo "$pname" >> /tmp/narthextemp.txt;
echo -n "Spouce name: "
read sname; echo "$sname" >> /tmp/narthextemp.txt;
#echo "Other keywords (separated by space): "
#read other

cat /tmp/narthextemp.txt | sed '/^$/d' | tr -d ' ' | nhance | ninc 1 30 | nleet > "${name}".txt
rm /tmp/narthextemp.txt
echo "[!] Exported at $name.txt"
