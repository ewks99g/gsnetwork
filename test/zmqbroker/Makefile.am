AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=brokerserver
brokerserver_SOURCES=main.cpp
INCLUDES=-I../include -I../../module/zmqware -I/usr/local/include -I/usr/include 
LDADD=-L/usr/local/lib -L/usr/lib -L/lib -L../../module/zmqware -lzmqwrap -lzmq 
DEFS=-DLINUX 
