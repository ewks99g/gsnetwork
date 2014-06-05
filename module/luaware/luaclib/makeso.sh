#g++ mytestlib.c -I/usr/local/include -shared -fPIC -o mytestlib.so
g++ gamemath.c -I/usr/local/include -fPIC -shared -ldl -o game_math_lib.so
