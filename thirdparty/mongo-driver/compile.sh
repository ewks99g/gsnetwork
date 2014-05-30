#!/bin/bash

if !(test -e /usr/bin/scons)
then
	sudo yum install scons
fi

scons


