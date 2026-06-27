#ifndef FUNCS_H
#define FUNCS_H

#include "includes.h"

int luaCreateWinWrapper(lua_State* L);
int luaSetWinBackColorWrapper(lua_State* L);
int luaWinShouldCloseWrapper(lua_State* L);
int luaVertSyncWrapper(lua_State* L);
int luaSetWinPosWrapper(lua_State* L);
int luaSwapBuffersWrapper(lua_State* L);
int luaPollEventsWrapper(lua_State* L);
int luaDrawTerminateWrapper(lua_State* L);
int luaGetKeyWrapper(lua_State* L);
#endif