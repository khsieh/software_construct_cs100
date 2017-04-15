#!/bin/bash

# my_find.sh
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

#set up for path
if [ $# -eq 0 ];
    then path="$PWD"
else
	if [ $1 != "-name" ] && [ $1 != "-print" ] && [ $1 != "-type" ] && [ $1 != "-exec" ]; then
		path=$1
		if [ $1 = "." ]; then
			path="$PWD"
		fi
	else
		path="$PWD"
	fi
fi

printTerminal=0

while [ $# -ge 1 ]; do
	if [ $1 = "-name" ]; then 
		shift
		filename=$1
	
	elif [ $1 = "-type" ]; then 
		shift
		filetype=$1

	else
		if [ $1 = "-print" ]; then
			printTerminal=1
		elif [ $1 = "-exec" ]; then
			shift
			execute=$(echo $@ | tr -d "{};")
		fi
	fi

shift
done

# echo "path is $path"
# echo "filename is $filename"
# echo $execute

for var in $(ls -R $path)
do
	if [ -z $filetype ]; then 
		echo $path/$var
	elif [ -$filetype $path/$var -a "$var" == "$filetype" ]; then 
		echo $path/$var
		if [ ! -z "$execute" ]; then
			$execute $path/$var
	fi
	fi

done
