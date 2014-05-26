#!/bin/bash
sudo pkill cgiserver
sudo /usr/local/nginx/sbin/spawn-fcgi -a 127.0.0.1 -p 8088 -f ./cgiserver 
