AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=mongotest
mongotest_SOURCES=main.cpp DBTest.cpp
INCLUDES=-I../../module/mongoware -I../../thirdparty/mongo-driver/src -I/usr/local/include -I/usr/include 
LDADD=-L/usr/local/lib -L/usr/lib -L/lib -L../../module/mongoware -L../../thirdparty/mongo-driver -lmongoware -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options -lpthread 
DEFS=-DLINUX 
