cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(open-engine-tools)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)

add_executable(GameServer
    game-server/GameServer.cpp)
set_target_options(GameServer)
#target_link_libraries(GameServer PRIVATE general gmock)
