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
	lua_close(m_pLuaState);
}

bool LuaInstance::init()
{
	lua_state_ = lua_open();
	
	luaopen_base(lua_state_);
	luaopen_table(lua_state_);
	luaopen_debug(lua_state_);
	luaopen_math(lua_state_);

	return true;
}

