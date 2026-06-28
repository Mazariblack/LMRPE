#include "funcs.h"
#include "luacompile.h"

int main() {
    LuaScript luaScr("./scripts/");
    luaScr.compile();
}