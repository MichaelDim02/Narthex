#!/bin/sh

version="1.0"
RED='\033[0;31m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
GREY='\033[0;37m'
NC='\033[0m'

printf "\n"
printf "${GREEN}                  .                              \n"; sleep 0.05;
printf "                                                         \n"; sleep 0.05;
printf "                   .${NC}                                \n"; sleep 0.05;
printf "${YELLOW}         /^\ ${NC}     ${GREEN}.${NC}           \n"; sleep 0.05;
printf "${RED}    /\ ${NC}  ${YELLOW}\"V\"${NC}                  \n"; sleep 0.05;
printf "${RED}   /__\ ${NC}  I    ${GREEN}  O  o   ${NC}         \n"; sleep 0.06;
printf "${RED}  //${NC}..${RED}\\\\\\  ${NC}I${GREEN}     . ${NC}\n"; sleep 0.06;
printf "${RED}  \]${NC}.\`${RED}[/${NC}  I   ${GREEN}       ${NC}\n"; sleep 0.06;
printf "${RED}  /l\/j\ ${NC} (]   ${GREEN} .  O     ${NC}        \n"; sleep 0.06;
printf "${RED} /. ~~ ,\\/${NC}I   ${GREEN}       .  ${NC}        \n"; sleep 0.07;
printf "${RED} \\\\\\L__j^\/${NC}I ${GREEN}      o  ${NC}        \n"; sleep 0.07;
printf "${RED}  \/-- }  ${NC}I    ${GREEN} o   .    ${NC}        \n"; sleep 0.08;
printf "${RED}  |I  N|  ${NC}I${GREY}   _________   ${NC}        \n"; sleep 0.08;
printf "${RED}  |C  I|  ${NC}I${GREY} c(         )o ${NC}        \n"; sleep 0.09;
printf "${RED}  |X  Kl  ${NC}I${GREY}   \.     ,/   ${NC}        \n"; sleep 0.1;
printf "${RED}_/ C  A \_${NC}!${GREY}  _//^---^\\\\_${NC}    -Row\n"; sleep 0.1;
printf "\n"; sleep 1;
# The ASCII art was originally created by Row. It has been modified.

printf "${GREEN}NARTHEX ELDER $version\n"; sleep 0.1;
printf "Wizard program for Narthex ${NC}\n"; sleep 0.1;
printf "By Michael Constantine Dimopoulos\n"; sleep 0.1;
printf "https://mcdim.xyz  <mk@mcdim.xyz>\n\n"; sleep 0.5;

printf "${RED}You will be asked a couple of questions regarding the target.\n"; sleep 2;
printf "And Narthex will generate a personalized wordlist based on the information.\n"; sleep 2;
printf "You are encouraged to edit the nwiz.sh file yourself.${NC}\n\n"; sleep 2;
printf "Leave as many blank as you like\n\n"

printf "${RED}-Questions-${NC}\n"
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
