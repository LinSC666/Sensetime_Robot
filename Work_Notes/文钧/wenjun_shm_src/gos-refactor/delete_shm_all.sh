#!/bin/bash
lsof_ret=$(lsof /dev/shm)
for name in $(ls /dev/shm)
do
	lsof_name_ret=$(grep $name <<< $lsof_ret)
	if [ -z "$lsof_name_ret" ]
	then
		if [ -n "$(grep 'gos.*' <<< $name)" ]
		then
			echo $name
			rm -f "/dev/shm/$name"
		fi
	fi
done
