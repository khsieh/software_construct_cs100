# my_which.sh
# Course: CS 100 Fall 2013
# 
# First Name: <Kevin>
# Last Name: <Hsieh>
# Username: <khsie003>
# email address: <khsie003@ucr.edu>
# 
# Assignment: <Homework #7>
# 
# I hereby certify that the contents of this file represent
# my own original individual work. Nowhere herein is there
# code from any outside resources such as another individual,
# a website, or publishings unless specifically designated as
# permissible by the instructor or TA.

#!/bin/bash
OIFS=$IFS
IFS=':'	

for var in "$@"
do
	paths=$PATH

	for p in $paths
	do
		curPath=$p'/'$var
		if test -f $curPath
			then
				echo $curPath
		fi
	done

done

IFS=$OIFS