#!/bin/sh

printf "$(curl -s file:///var/lib/narthex/elder.txt)\n"

echo "=Questions="
echo -n "Name: "
read n; echo "$n" >> /tmp/nrthxtmp;
echo -n "Last name: "
read lname; echo "$lname" >> /tmp/nrthxtmp;
echo -n "Nickname: "
read nn;echo "$nn" >> /tmp/nrthxtmp;
echo -n "Birthday: "
read bd; echo "$bd"  >> /tmp/nrthxtmp;
echo -n "Birthyear: "
read by;echo "$by" >> /tmp/nrthxtmp;
echo -n "Phone number: "
read phn; echo "$phn" >> /tmp/nrthxtmp;
echo -n "Pet name: "
read pn; echo "$pn" >> /tmp/nrthxtmp;
echo -n "Current City: "
read cy; echo "$cy" >> /tmp/nrthxtmp;
echo -n "Spouse name: "
read sn; echo "$sn" >> /tmp/nrthxtmp;
echo "Other keywords (separated by space): "
read o; echo "$o"| tr " " "\n" >> /tmp/nrthxtmp;

cat /tmp/nrthxtmp | sed '/^$/d' | tr -d ' ' | nhance | ncom -b | ninc 1 30 | nleet > "${n}".txt
rm /tmp/nrthxtmp
echo "[!] Exported at $n.txt"
