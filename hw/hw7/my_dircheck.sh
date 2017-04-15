# my_dircheck.sh
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
for var in "$@"
do
	if test -d "$var"
		then 
			echo "$var:\n"
			
			echo "Number of Subdirectories: " $(find "$var"/* -type d | wc -l)
			echo "Number of Files: " $(find "$var"/* -type f | wc -l)
			echo "List of files with Zero Length:\n$(find $var -size 0 )"
			echo "Disk Usage: " $(du "$var" -h -s)
			echo
	else
		echo "$var is not a directory"
	fi
done