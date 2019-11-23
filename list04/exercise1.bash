#!/bin/bash

	interface=$1
	time=1
	TOTAL2=0

 	RECEIVED1=`grep $1 /proc/net/dev | sed s/.*:// | awk '{print $1}'`
  	TRANSMITTED1=`grep $1 /proc/net/dev | sed s/.*:// | awk '{print $9}'`
	sleep 1;

	show()
	{
	if (($1<1024)); 
		then
		echo "$1 B/s"
		elif (($1 >=1024 && $1<1048576));
		then
		echo "$(echo "$1/1024" | bc) KB/s"
		else 
		echo "$(echo "$1/1048576" | bc) MB/s"
		fi
	}

	while sleep 1
	do 
	clear

	awk '{print "Time of running system:"  int($1/86400)":"int($1/3600)":"int(($1%3600)/60)":"int($1%60)} ' /proc/uptime;

	upower -i /org/freedesktop/UPower/devices/battery_BAT0| grep -E "to\ full|percentage";

	awk '{print "Load avarage: " $1}' /proc/loadavg;

 	TOTAL=$(($RECEIVED1+$TRANSMITTED1))
	
  	RECEIVED2=`grep $1 /proc/net/dev | sed s/.*:// | awk '{print $1}'`
  	TRANSMITTED2=`grep $1 /proc/net/dev | sed s/.*:// | awk '{print $9}'`
  	SPEED=$((($RECEIVED2+$TRANSMITTED2-$TOTAL)/1))
	TOTAL2=$(($RECEIVED2 + $TRANSMITTED2 + $TOTAL2 - $TOTAL))

	AVG=$((($TOTAL2)/($time)));
	echo "Actual speed: $(show $SPEED)" ;
	echo "Avg speed: $(show $AVG)";

	RECEIVED1=$RECEIVED2
	TRENSMITTED1=$TRANSMITTED2
	let "time += 1";
	
	done

