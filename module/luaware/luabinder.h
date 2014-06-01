/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/05/31
******************************************************************/
#ifndef __MODULE_LUAWARE_LUABINDER__
#define __MODULE_LUAWARE_LUABINDER__
#include "lua.hpp"

namespace luabinder
{
	template<typename T>
	void push(lua_State *L, T ret);

	template<typename T>
	T read(lua_State* L, int index);
	
	template<typename T>
	T pop(lua_State *L)
	{
		 T t = read<T>(L, -1); 
		 lua_pop(L, 1); 
		 return t;
	}
};

#endif
