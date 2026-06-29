#ifndef FUNCS_H
#define FUNCS_H

#include "includes.h"

class LuaWrapper{
public:
	static int luaCreateWinWrapper(lua_State* L);
	static int luaSetWinBackColorWrapper(lua_State* L);
	static int luaWinShouldCloseWrapper(lua_State* L);
	static int luaVertSyncWrapper(lua_State* L);
	static int luaSetWinPosWrapper(lua_State* L);
	static int luaSwapBuffersWrapper(lua_State* L);
	static int luaPollEventsWrapper(lua_State* L);
	static int luaDrawTerminateWrapper(lua_State* L);
	static int luaGetKeyWrapper(lua_State* L);
	static int luaMAllocWrapper(lua_State* L);
	static int luaMDeallocWrapper(lua_State* L);
	static int luaMForceDeallocWrapper(lua_State* L);
};
#endif