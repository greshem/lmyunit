#!/bin/bash
if [  ! $# -eq 1 ];then
	echo "Usage: $0 file.cpp"
	exit -1;
fi 
file=$1;
sed '/\.\.\.\.\.\./{s/.*/\/\/#####################################################################################/g}'  $file   -i
sed '/------------/{s/.*/\/\/#####################################################################################/g}'  $file   -i

