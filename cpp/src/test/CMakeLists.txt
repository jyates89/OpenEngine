cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(open-engine-testing)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)

add_executable(MessageBusTesting message-bus/MessageBusTest.cpp)
set_target_options(MessageBusTesting)
target_link_libraries(MessageBusTesting PRIVATE general gmock)

add_test(NAME MessageBusTesting
    COMMAND MessageBusTesting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
