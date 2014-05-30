#!/bin/bash

##############################################################################
##config nginx
if test -e /usr/local/nginx/logs/nginx.pid
then
	sudo kill -QUIT `cat /usr/local/nginx/logs/nginx.pid`
fi

if test -e /usr/local/nginx/sbin/nginx 
then
	sudo /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf
fi

##############################################################################
##config http resouce dir and file
if !(test -d /var/www)
then
	sudo mkdir /var/www
fi
if !(test -e /var/www/demo.cgi)
then
	echo "Hello world,CGI" > /var/www/demo.cgi
fi

##############################################################################
##config cgi
sudo iptables -F
sudo pkill cgiserver
sudo /usr/local/nginx/sbin/spawn-fcgi -a 127.0.0.1 -p 8088 -f ./cgiserver 

##############################################################################
##test uri
###http://192.168.1.4/demo.cgi?key=4&value=5
