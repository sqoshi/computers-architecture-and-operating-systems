#!/bin/bash
cd history
name="${1///}"
lynx -dump $1 > $name
while [ true ]
do
	sleep $2
	lynx -dump $1 > tmp
	diff $name tmp > "history $name"
	if [ -s "history $name" ]
	then
		echo -e  "\e[5m changes spotted \e[0m"
	else
		echo "nothing changed"
	fi
	lynx -dump $1 >$name
done
