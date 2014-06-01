/*******************************************************************
*  Copyright(c) 2000-2013 linghegu
*  All rights reserved.
*  Author: 	wangbin
*  Email:  	wang70bin@163.com
*  CreateTime: 2014/06/01
******************************************************************/
#ifndef __MODULE_LUAWARE_LUAFUNCSRC_H__
#define __MODULE_LUAWARE_LUAFUNCSRC_H__

//extern "C"
static int 
test_add_two_int(lua_State* L);

static int
test_sub_two_int(lua_State* L);


int register_c_func(lua_State* L);
#endif
