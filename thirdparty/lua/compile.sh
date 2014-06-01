#!/bin/bash


if !(test -e /usr/local/lib/libreadline.so)
then
	sudo apt-get install libreadline6 libreadline6-dev
fi

make clean
make linux
