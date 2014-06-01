/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/06/01
******************************************************************/

//extern "C"
#include "lua.hpp"
#include "luafuncsrc.h"	
	
int 
test_add_two_int(lua_State* L){
	int op1 = luaL_checkinteger(L,1);
	int op2 = luaL_checkinteger(L,2);
	
	printf("call c fun test_add_two_int,%d,%d",op1,op2);
	lua_pushinteger(L,op1 + op2);

	return 1;
}

int 
test_sub_two_int(lua_State* L) {
	int op1 = luaL_checkinteger(L,1);
	int op2 = luaL_checkinteger(L,2);
	
	lua_pushinteger(L,op1 - op2);

	return 1;		//return result number
}


/*******************************************************************/
int register_c_func(lua_State* L){
	lua_register(L,"add_two_int",test_add_two_int);
	lua_register(L,"sub_two_int",test_sub_two_int);
}
