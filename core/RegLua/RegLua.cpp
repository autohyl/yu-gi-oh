#include "RegLua.h"
#include <muduo/base/Logging.h>

void LogInfo(const char *strMsg) {
    LOG_INFO << strMsg;
}

void Y_RegAll(struct lua_State *pLState) {
    luabridge::getGlobalNamespace(pLState)
        .addFunction("LogInfo", LogInfo);
}