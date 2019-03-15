cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(google-mock-test)

add_executable(${PROJECT_NAME} GoogleMockTest.cpp)
include(${CMAKE_SOURCE_DIR}/cmake/common_include.cmake)

target_link_libraries(${PROJECT_NAME} PRIVATE general gmock)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)
if(CMAKE_VERBOSE)
    print_configuration_output(${PROJECT_NAME})
    write_generator_output(${PROJECT_NAME})
endif()

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
