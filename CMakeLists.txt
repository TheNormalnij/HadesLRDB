cmake_minimum_required(VERSION 3.20)

project(HadesLRDB VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/lua-5.2.2)
add_subdirectory(module)

install(TARGETS HadesLRDB
        RUNTIME
        DESTINATION ${CMAKE_SOURCE_DIR}/bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/module/scripts/
        DESTINATION ${CMAKE_SOURCE_DIR}/bin
)
