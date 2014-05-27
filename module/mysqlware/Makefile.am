noinst_LIBRARIES=libmysqlware.a
libmysqlware_a_SOURCES=inc/DBDefine.h\
						inc/DBManager.h\
						inc/DBUtil.h \
						inc/SqlCommand.h\
						inc/SqlDataReader.h\
						src/DBManager.cpp \
						src/DBUtil.cpp \
						src/SqlCommand.cpp \
						src/SqlDataReader.cpp
INCLUDES=-I./inc/ -I/usr/local/include/mysql -I/usr/local/include -I/usr/include
LDADD=-L/usr/local/lib -L/usr/lib -L/lib
DEFS=-DLINUX
