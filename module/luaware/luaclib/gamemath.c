#include <stdio.h>
#include <string.h>
#include "lua.hpp"

extern "C" 
int add(lua_State* L) 
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 + op2);
    return 1;
}
 
extern "C" 
int sub(lua_State* L)
{
    double op1 = luaL_checknumber(L,1);
    double op2 = luaL_checknumber(L,2);
    lua_pushnumber(L,op1 - op2);
    return 1;
}
static luaL_Reg math_lib_name[] = { 
    {"add_two_num", add},
    {"sub_two_num", sub},
    {NULL, NULL} 
}; 
 
extern "C"
int luaopen_game_math_lib(lua_State* L) 
{
    const char* libName = "game_math_lib";
	luaL_newlib(L,math_lib_name);
    return 1;
}
