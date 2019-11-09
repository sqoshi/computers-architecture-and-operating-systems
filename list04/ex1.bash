#!bin/bash

#filling column values as 0 before first drawSystemLoadGraph call
for (( i=0; i<10; i++))
do
    arr[$i]=0; 
done

function transferFormat {
    if [ $1 -ge 1048576 ] 
    then
        let "v1 = v1 / 1048576"
        echo "Current transmission speed: $1 MB (enp0s3)"
    elif [ $1 -ge 1024 ] 
    then
        let "v1 = v1 / 1024"
        echo "Current transmission speed: $1 kB (enp0s3)"
    else
        echo "Current transmission speed: $1 B (enp0s3)"
    fi
    
    if [ $2 -ge 1048576 ] 
    then
        let "v1 = v1 / 1048576"
        echo "Average transmission speed: $2 MB (enp0s3)"
    elif [ $1 -ge 1024 ] 
    then
        let "v1 = v1 / 1024"
        echo "Average transmission speed: $2 kB (enp0s3)"
    else
        echo "Average transmission speed: $2 B (enp0s3)"
    fi
}

function transferDisplay {
    v1=$(grep -w enp0s3 /proc/net/dev | awk '{print $10}')
    
    let "v1 = v1 - $1"
    let "avg = ($3 * ($2 - 1) + v1)/$2"
    
    transferFormat $v1 $avg
    
    lastAvg=$avg
}

function uptimeDisplay {
    v1=$(cat /proc/uptime | awk '{print $1}')
    v1=${v1/\.*/}
    let "h = v1 / 3600"
    let "m=(($v1 % 3600)/60)"
    let "s = $v1 % 60"
    printf "Runnig time: %02d:%02d:%02d\n" $h $m $s
}

function powerSupplyDisplay {
    v1=$(grep -w "POWER_SUPPLY_ENERGY_NOW=*" /sys/class/power_supply/BAT0/uevent | sed 's/POWER_SUPPLY_ENERGY_NOW=//g')
    v2=$(grep -w "POWER_SUPPLY_ENERGY_FULL=*" /sys/class/power_supply/BAT0/uevent | sed 's/POWER_SUPPLY_ENERGY_FULL=//g')
    let "v1 =  v1 * 100 / v2 "
    echo "Battery supply: $v1%"
}

function loadAvqDisplay {
    v1=$(cat /proc/loadavg | awk '{print $1}')
    echo "System load avg in last minute: $v1"
}

function drawSystemLoadGraph {
    v1=$(bc<<<$v1*100)
    v1=${v1/\.*/}
    let "v1 = v1 / 10"
    
    tput cup 6 17 ; echo 'System load';
    tput cup 11 50 ; echo ' A - is an actual load state'
    tput cup 12 50 ; echo ' x from {1,...,9} are states x seconds ago' 
    
    tput cup 8 0 ; echo '1.0 |'  ;
    tput cup 9 0 ; echo '0.9 | ' ;
    tput cup 10 0 ; echo '0.8 |' ;
    tput cup 11 0 ; echo '0.7 |' ;
    tput cup 12 0 ; echo '0.6 |' ;
    tput cup 13 0 ; echo '0.5 |' ;
    tput cup 14 0 ; echo '0.4 |' ;
    tput cup 15 0 ; echo '0.3 |' ;
    tput cup 16 0 ; echo '0.2 |' ;
    tput cup 17 0 ; echo '0.1 |' ;
    tput cup 18 7 ; echo 'A   1   2   3   4   5   6   7   8   9' ;
    
    #setting values for each column
    for (( i=9; i>0; i--))
    do
        let "j = i - 1"
        arr[$i]=${arr[$j]} 
    done
    arr[0]=$v1
    
    #columns drawing
    x=0
    for (( j=7; j<=43; j=j+4 ))
    do
        for (( i=17; i>(17-${arr[$x]}); i-- ))
        do
            tput cup $i $j ; echo '|' ;
        done
        let "x = x + 1"
    done
}

itNumber=0
lastAvg=0

while [ true ] 
do
    let "itNumber = itNumber + 1"
    value=$(grep -w enp0s3 /proc/net/dev | awk '{print $10}')
    
    sleep 1
    clear
    
    transferDisplay value itNumber lastAvg
    uptimeDisplay
    powerSupplyDisplay
    loadAvqDisplay
    drawSystemLoadGraph
done

