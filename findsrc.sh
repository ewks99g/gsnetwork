#!/bin/bash

#check xsel
if [ `which xsel` == "" ]; then
	echo "the command xsel does not exists!"
    exit 0
fi

clear

content=`xsel`
if [ $? -gt 0 ]
then	
	content=$1
fi

grep $content ./* -RnH --color=auto --binary-files=without-match
