cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(doxygen-test)

add_executable(${PROJECT_NAME}
    DoxygenTest.cpp)

include(${CMAKE_SOURCE_DIR}/cmake/common_include.cmake)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)
if(CMAKE_VERBOSE)
    print_configuration_output(${PROJECT_NAME})
    write_generator_output(${PROJECT_NAME})
endif()

