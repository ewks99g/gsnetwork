/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/29
******************************************************************/
#ifndef __MODULE_LUAWARE_LUAINSTANCE_H__
#define __MODULE_LUAWARE_LUAINSTANCE_H__

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};

class LuaInstance
{
	public:
		LuaInstance();
		~LuaInstance();
	public:
		bool init();
	private:
		lua_State*	lua_state_;
};

#endif
