AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=testserver
testserver_SOURCES=main.cpp
INCLUDES=-I../include -I../../zmqware -I/usr/local/include -I/usr/include 
LDADD=-L/usr/local/lib -L/usr/lib -L/lib -L../../zmqware -lzmqwrap -lzmq 
DEFS=-DLINUX 
