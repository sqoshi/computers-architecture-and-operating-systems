#!bin/bash
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
		echo "changes spotted"
	fi
	lynx -dump $1 >$name
done
