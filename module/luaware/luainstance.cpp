/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/29
******************************************************************/
#include <stdlib.h>
#include "luabinder.h"
#include "luainstance.h"
#include "luafuncsrc.h"

LuaInstance::LuaInstance()
{

}

LuaInstance::~LuaInstance()
{
	lua_close(lua_state_);
}

bool LuaInstance::init()
{
	//lua_state_ = lua_newstate(l_alloc,0);
	lua_state_ = luaL_newstate();
	if (NULL == lua_state_)
		return false;

	luaopen_base(lua_state_);
	luaopen_table(lua_state_);
	luaopen_string(lua_state_);
	luaopen_debug(lua_state_);
	luaopen_math(lua_state_);
	luaL_openlibs(lua_state_);
	return true;
}

bool LuaInstance::load_lua_head_file(const char* filename)
{
	if (luaL_loadfile(lua_state_,filename) != LUA_OK) {
		printf("can not load file %s,%s\n",filename,lua_tostring(lua_state_,-1));
		return false;
	}
	if (lua_pcall(lua_state_, 0, 0, 0) > 0)	{	//enter through lua env,make function and data active, pure dynamic language
		printf("can not pcall(L,0,0,0) to dynamic load content,%s\n",lua_tostring(lua_state_,-1));
		return false;
	}
	//			||
	//luaL_dofile(lua_state_,filename);

	return true;
}

bool LuaInstance::register_lua_func()
{
	register_c_func(lua_state_);
}

void LuaInstance::lua_perror(int errcode)const
{
	switch (errcode) {
		case LUA_YIELD:
			printf("Thread by suspended\n"); break;
		case LUA_ERRRUN:
			printf("Runtime error\n");break;
		case LUA_ERRSYNTAX:
			printf("Syntax error\n");break;
		case LUA_ERRMEM:
			printf("Mem error\n");break;
		case LUA_ERRERR:
			printf("Error of error handle\n");break;
		default:
			break;
	}
}
//////////////////////////////////////////////////////////////////////
void *l_alloc (void *ud, void *ptr, size_t osize,size_t nsize) 
{
    (void)ud;  (void)osize;  /* not used */
    if (nsize == 0) {
        free(ptr);
        return NULL;
    }
    else
        return realloc(ptr, nsize);
}
