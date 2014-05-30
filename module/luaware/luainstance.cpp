/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/29
******************************************************************/
#include "luainstance.h"

LuaInstance::LuaInstance()
{

}

LuaInstance::~LuaInstance()
{
	lua_close(lua_state_);
}

bool LuaInstance::init()
{
	lua_state_ = lua_open();
	if (NULL == lua_state_)
		return false;

	luaopen_base(lua_state_);
	luaopen_table(lua_state_);
	luaopen_string(lua_state_);
	luaopen_debug(lua_state_);
	luaopen_math(lua_state_);

	return true;
}

bool LuaInstance::load_lua_head_file(const char* filename)
{
	if (luaL_loadfile(lua_state_,filename) > 0)
		return true;
	return false;
}
