#include "includes.h"
#include "funcs.h"

unsigned int SC_WIDTH = 800;
unsigned int SC_HEIGHT = 400;

lua_State* L = nullptr;

int main() {
    std::cout << "[CINF] Compiling lua scripts" << std::endl;
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, luaCreateWinWrapper);
    lua_setglobal(L, "createWindow");

    lua_pushcfunction(L, luaSetWinBackColorWrapper);
    lua_setglobal(L, "setBackColor");

    lua_pushcfunction(L, luaWinShouldCloseWrapper);
    lua_setglobal(L, "windowShouldClose");

    lua_pushcfunction(L, luaVertSyncWrapper);
    lua_setglobal(L, "setVertSync");

    lua_pushcfunction(L, luaSetWinPosWrapper);
    lua_setglobal(L, "setWinPos");

    lua_pushcfunction(L, luaSwapBuffersWrapper);
    lua_setglobal(L, "swapBuffers");

    lua_pushcfunction(L, luaPollEventsWrapper);
    lua_setglobal(L, "pollEvents");

    lua_pushcfunction(L, luaDrawTerminateWrapper);
    lua_setglobal(L, "closeWindow");

    if (luaL_dofile(L, "script.lua") != LUA_OK) {
        std::cout << "[CERR] Lua Error: " << lua_tostring(L, -1) << std::endl;
    }

    //lua_getglobal(L, "window");
    //GLFWwindow* window = (GLFWwindow*)lua_touserdata(L, -1);

    //if (!window) {
    //    std::cout << "[CINF] Window creation cancelled" << std::endl;
    //}
    //else {
    //    glViewport(0, 0, SC_WIDTH, SC_HEIGHT);

    //    while (!glfwWindowShouldClose(window)) {
    //        glClear(GL_COLOR_BUFFER_BIT);

    //        glfwSwapBuffers(window);
    //        glfwPollEvents();
    //    }

    //    lua_close(L);
    //    glfwTerminate();
    //    return 0;
    //}
    lua_close(L);
    return 0;
}