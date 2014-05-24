AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=cgiserver
cgiserver_SOURCES=main.cpp
INCLUDES=-I/usr/local/include -I/usr/include 
LDADD=-L/usr/local/lib -L/usr/lib -L/lib -lpthread  -lfastcgipp -lmysqlclient -lboost_thread -lboost_thread-mt 
DEFS=-DLINUX 
