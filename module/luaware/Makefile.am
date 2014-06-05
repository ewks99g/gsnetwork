bin_PROGRAMS=luatest
luatest_SOURCES=main.cpp luainstance.cpp luabinder.cpp
INCLUDES=-I/usr/local/include -I/usr/include
LDADD=-L/usr/local/lib -L/usr/lib -L/lib -llua -ldl
AM_LDFLAGS=-rdynamic #g++'s flag
#DEFS=-Wl -E ###gcc's flag
