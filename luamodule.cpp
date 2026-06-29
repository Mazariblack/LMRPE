#include "lua/lua.hpp"
#include "funcs.h"

std::vector<int*> allocMOrder = {};

int LuaWrapper::luaCreateWinWrapper(lua_State* L) {
    unsigned int width = (unsigned int)luaL_checkinteger(L, 1);
    unsigned int height = (unsigned int)luaL_checkinteger(L, 2);
    const char* title = luaL_checkstring(L, 3);

    std::cout << "[CINF] Initializing GLFW" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    std::cout << "[CINF] Creating window" << std::endl;
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cout << "[CINF] Window creating cancelled" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    std::cout << "[CINF] Initializing GLAD" << std::endl;
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "[CERR] Failed to initialize GLAD" << std::endl;
        return -1;
    }
    lua_pushlightuserdata(L, window);
    return 1;
}
int LuaWrapper::luaSetWinBackColorWrapper(lua_State* L) {
    GLfloat red = (float)luaL_checknumber(L, 1);
    GLfloat green = (float)luaL_checknumber(L, 2);
    GLfloat blue = (float)luaL_checknumber(L, 3);
    GLfloat alpha = (float)luaL_checknumber(L, 4);

    glClearColor(red/255, green/255, blue/255, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    return 0;
}
int LuaWrapper::luaWinShouldCloseWrapper(lua_State* L) {
    GLFWwindow* window = (GLFWwindow*)lua_touserdata(L, 1);

    lua_pushboolean(L, glfwWindowShouldClose(window));
    return 1;
}
int LuaWrapper::luaVertSyncWrapper(lua_State* L) {
    unsigned int value = (unsigned int)luaL_checkinteger(L, 1);

    glfwSwapInterval(value);
    return 0;
}
int LuaWrapper::luaSetWinPosWrapper(lua_State* L) {
    int PosX = (int)luaL_checkinteger(L, 2);
    int PosY = (int)luaL_checkinteger(L, 3);
    GLFWwindow* window = (GLFWwindow*)lua_touserdata(L, 1);

    glfwSetWindowPos(window, PosX, PosY);
    return 0;
}
int LuaWrapper::luaSwapBuffersWrapper(lua_State* L) {
    GLFWwindow* window = (GLFWwindow*)lua_touserdata(L, 1);

    glfwSwapBuffers(window);
    return 0;
}
int LuaWrapper::luaPollEventsWrapper(lua_State* L) {
    glfwPollEvents();
    return 0;
}
int LuaWrapper::luaDrawTerminateWrapper(lua_State* L) {
    GLFWwindow* window = (GLFWwindow*)lua_touserdata(L, 1);

    if (window != NULL) {
        glfwSetWindowShouldClose(window, true);
    }
    return 0;
}
int LuaWrapper::luaGetKeyWrapper(lua_State* L) {
    int key = (int)luaL_checkinteger(L, 2);
    GLFWwindow* window = (GLFWwindow*)lua_touserdata(L, 1);

    lua_pushboolean(L, glfwGetKey(window, key));
    return 1;
}
int LuaWrapper::luaMAllocWrapper(lua_State* L) {
    int mCount = (int)luaL_checkinteger(L, 1);

    std::cout << "[CINF] Allocating memory" << std::endl;
    int* alloc = (int*)malloc(mCount * sizeof(int));
    allocMOrder.push_back(alloc);

    int lastAllocIndex = allocMOrder.size() - 1;

    lua_pushinteger(L, lastAllocIndex);
    return 1;
}
int LuaWrapper::luaMDeallocWrapper(lua_State* L) {
    int allocMId = (int)luaL_checkinteger(L, 1);

    std::cout << "[CINF] Deallocating memory" << std::endl;
    if (allocMId >= 0 && allocMId < allocMOrder.size()) {
        if (allocMOrder[allocMId] != nullptr) {
            free(allocMOrder[allocMId]);
            allocMOrder[allocMId] = nullptr;
        }
    }

    return 0;
}
int LuaWrapper::luaMForceDeallocWrapper(lua_State* L) {
    std::cout << "[CINF] Force deallocating memory" << std::endl;
    for (size_t i = 0; i < allocMOrder.size(); ++i) {
        if (allocMOrder[i] != nullptr) {
            free(allocMOrder[i]);
            allocMOrder[i] = nullptr;
        }
    }

    return 0;
}