add_library(HadesLRDB SHARED)

add_definitions(-DASIO_HAS_STD_ADDRESSOF)
include_directories (
   src/.
   ../include
   ../libs/lua-5.2.2/src
   ../libs/lrdb/include
   ../libs/lrdb/third_party/asio/asio/include
   ../libs/lrdb/third_party/picojson
)

file(GLOB_RECURSE MOD_FILES src/*.cpp src/*.h)

target_sources(
    HadesLRDB
    PUBLIC
        ${MOD_FILES}
)

target_link_libraries(HadesLRDB PRIVATE lualib)
