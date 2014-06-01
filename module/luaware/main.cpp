#include <unistd.h>
#include <stdio.h>
#include "luainstance.h"

int
main()
{
	LuaInstance lua_instance;
	lua_instance.init();

//	if (!lua_instance.load_lua_head_file("./lua_entry.lua"))
	if (!lua_instance.load_lua_head_file("./luascript/game_math.lua"))
		return 0;

	lua_instance.register_lua_func();

	//lua_instance.call<int>("getMaxLevNum","test",0);
	printf("addNumber %d\n",lua_instance.call<int>("addNumber",10,20));
	printf("G_width%d\n",lua_instance.get_var<int>("G_width"));

	 sleep(100000);
}
