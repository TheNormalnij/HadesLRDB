--
-- Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
-- Licensed under the MIT license. See LICENSE file in the project root for details.
--

debug.lrdbHandler = debug.lrdb.activate(21110, false)

local function enableDebugConf()
    -- /DebugDraw=true /DebugKeysEnabled=true
    SetConfigOption { Name = "DebugDraw", Value = true }
    SetConfigOption { Name = "DebugKeysEnabled", Value = true }
end

enableDebugConf()

OnPreThingCreation { enableDebugConf }
