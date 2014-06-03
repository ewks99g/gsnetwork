#include <unistd.h>
#include <stdio.h>
#include "luainstance.h"
#include <dlfcn.h>

int
main()
{
	LuaInstance lua_instance;
	lua_instance.init();
	
//	void* dl_handle = dlopen("luaclib/mytestlib.so",RTLD_LAZY);
//	if (dlopen == NULL) {
//		printf("Can not load dl\n");
//		return 1;
//	}
	
//	int (*lua_addr)(lua_State*) = 0;
//	*(void **) (&lua_addr) = dlsym(dl_handle,"luaopen_mytestlib");
	//luaopen_mytestlib(NULL);
//	if (lua_addr) { printf("symbol add %x\n",lua_addr); lua_addr(0);}
//	else printf("Can not find symbol\n");


//	return 0;



	if (!lua_instance.load_lua_head_file("./lua_entry.lua"))
		return 0;

	lua_instance.register_lua_func();

	//lua_instance.call<int>("getMaxLevNum","test",0);
	printf("addNumber %d\n",lua_instance.call<int>("addNumber",10,20));
	printf("G_width%d\n",lua_instance.get_var<int>("G_width"));
	printf("config: %d\n",lua_instance.get_config_var<int>("game_monster_config","level"));
	printf("config: %s\n",lua_instance.get_config_var<const char*>("game_monster_config","desc"));

	 sleep(100000);
}
