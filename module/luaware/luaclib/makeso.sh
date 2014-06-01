#g++ mytestlib.c -I/usr/local/include -shared -fPIC -o mytestlib.so
g++ mytestlib.c -I/usr/local/include -fPIC -shared -ldl -o mytestlib.so
