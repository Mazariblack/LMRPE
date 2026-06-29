#pragma once
#include "funcs.h"

namespace fs = std::filesystem;

class LuaScript {
public:
    LuaScript(fs::path path) { this->path = path; }

    int compile() {
        std::cout << "[CINF] Compiling lua scripts" << std::endl;
        if (fs::exists(path) && fs::is_directory(path)) {
            std::vector<std::thread> threads;

            for (const auto& script : fs::directory_iterator(path)) {
                if (fs::is_regular_file(script) && script.path().extension() == ".lua") {
                    std::cout << "[CINF] LUA Script found: " << script.path().filename() << std::endl;
                    threads.emplace_back(&LuaScript::loadScript, this, script.path());
                }
            }

            for (auto& t : threads) {
                if (t.joinable()) {
                    t.join();
                }
            }
        }
        else {
            std::cout << "[CERR] LUA Scripts directory path not found" << std::endl;
            return -1;
        }
        return 0;
    }

private:
    fs::path path;

    void loadScript(fs::path scriptPath) {
        lua_State* L = luaL_newstate();
        if (!L) return;

        luaL_openlibs(L);

        std::map<std::string, lua_CFunction> luaCfuncs = {
            {"createWindow", LuaWrapper::luaCreateWinWrapper},
            {"setBackColor", LuaWrapper::luaSetWinBackColorWrapper},
            {"windowShouldClose", LuaWrapper::luaWinShouldCloseWrapper},
            {"setVertSync", LuaWrapper::luaVertSyncWrapper},
            {"setWinPos", LuaWrapper::luaSetWinPosWrapper},
            {"swapBuffers", LuaWrapper::luaSwapBuffersWrapper},
            {"pollEvents", LuaWrapper::luaPollEventsWrapper},
            {"closeWindow", LuaWrapper::luaDrawTerminateWrapper},
            {"getKey", LuaWrapper::luaGetKeyWrapper},
            {"mAlloc", LuaWrapper::luaMAllocWrapper},
            {"mDealloc", LuaWrapper::luaMDeallocWrapper},
            {"mForceDealloc", LuaWrapper::luaMForceDeallocWrapper}
        };

        for (const auto& [name, func] : luaCfuncs) {
            lua_pushcfunction(L, func);
            lua_setglobal(L, name.c_str());
        }

        lua_pushinteger(L, GLFW_PRESS);
        lua_setglobal(L, "KEY_PRESS");

        if (luaL_dofile(L, scriptPath.string().c_str()) != LUA_OK) {
            std::cout << "[CERR] Lua Error: " << lua_tostring(L, -1) << std::endl;
        }

        lua_close(L);
    }
};