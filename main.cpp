#include "funcs.h"

unsigned int SC_WIDTH = 800;
unsigned int SC_HEIGHT = 400;

lua_State* L = nullptr;

int main() {
    std::cout << "[CINF] Compiling lua scripts" << std::endl;
    L = luaL_newstate();
    luaL_openlibs(L);

    std::map<std::string, 
        lua_CFunction> luaCfuncs = { 
            {"createWindow", luaCreateWinWrapper},
            {"setBackColor", luaSetWinBackColorWrapper},
            {"windowShouldClose", luaWinShouldCloseWrapper},
            {"setVertSync", luaVertSyncWrapper},
            {"setWinPos", luaSetWinPosWrapper},
            {"swapBuffers", luaSwapBuffersWrapper},
            {"pollEvents", luaPollEventsWrapper},
            {"closeWindow", luaDrawTerminateWrapper},
            {"getKey", luaGetKeyWrapper}};

    for (const auto& [name, func] : luaCfuncs) {
        lua_pushcfunction(L, func);
        lua_setglobal(L, name.c_str());
    } 

    lua_pushinteger(L, GLFW_PRESS);
    lua_setglobal(L, "KEY_PRESS");

    if (luaL_dofile(L, "script.lua") != LUA_OK) {
        std::cout << "[CERR] Lua Error: " << lua_tostring(L, -1) << std::endl;
    }
    lua_close(L);
    return 0;
}