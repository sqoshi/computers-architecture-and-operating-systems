#!bin/bash
echo "Name PID PPID State TGID RunningFiles"
for id in /proc/*/ ; do
    if [ -f "$id"status ] 
    then 
        v1=$(grep -w Name "$id"status | awk '{print $2}')
        v2=$(grep -w Pid "$id"status | awk '{print $2}')
        v3=$(grep -w PPid "$id"status | awk '{print $2}')
        v4=$(grep -w State "$id"status | awk '{print $2}')
        v5=$(grep -w Tgid "$id"status | awk '{print $2}')
        if [ -x "$id"fd ] 
        then
            v6=$(ls "$id"/fd | wc -l)
        else 
            v6=$(echo "?")
        fi    
        echo "$v1 $v2 $v3 $v4 $v5 $v6"
    fi
done

