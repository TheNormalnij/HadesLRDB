//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include <cstdint>
#include "../include/HadesModApi.h"

#include <lrdb/server.hpp>

using server_ptr = std::unique_ptr<lrdb::server>;

static int lrdb_activate(lua_State *L) {
    server_ptr *server = (server_ptr *)lua_touserdata(L, lua_upvalueindex(1));
    uint16_t port = 21110;
    bool blockThread = false;
    if (lua_isnumber(L, 1)) {
        port = lua_tonumber(L, 1);
    }
    if (lua_isboolean(L, 2)) {
        blockThread = lua_toboolean(L, 2);
    }

    server->reset(new lrdb::server(port));
    // Hack
    bool *waitForConnect = reinterpret_cast<bool*>(server->get());
    *waitForConnect = blockThread;
    //
    (*server)->reset(L);
    return 0;
}

static int lrdb_deactivate(lua_State *L) {
    server_ptr *server = (server_ptr *)lua_touserdata(L, lua_upvalueindex(1));
    server->reset();
    return 0;
}

static int lrdb_destruct(lua_State *L) {
    server_ptr *server = (server_ptr *)lua_touserdata(L, 1);
    server->~server_ptr();
    return 0;
}

HADES_MOD_API void _cdecl HadesModLuaCreated(lua_State *L) {
    lua_getglobal(L, "debug");
    int debug = lua_gettop(L);

    lua_createtable(L, 0, 3);
    int mod = lua_gettop(L);

    void *storage = lua_newuserdata(L, sizeof(server_ptr));
    new (storage) server_ptr();
    int sserver = lua_gettop(L);
    lua_createtable(L, 0, 1);
    lua_pushcclosure(L, &lrdb_destruct, 0);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, sserver);
    lua_pushvalue(L, sserver);
    lua_pushcclosure(L, &lrdb_activate, 1);
    lua_setfield(L, mod, "activate");
    lua_pushvalue(L, sserver);
    lua_pushcclosure(L, &lrdb_deactivate, 1);
    lua_setfield(L, mod, "deactivate");

    lua_pop(L, 1);
    lua_setfield(L, debug, "lrdb");
};

HADES_MOD_API bool _cdecl HadesModInit(const IModApi *modApi) {
    if (modApi->version < MOD_API_VERSION)
        return false;

    return true;
};

HADES_MOD_API bool _cdecl HadesModStart() { return true; };

HADES_MOD_API bool _cdecl HadesModStop() { return true; };
