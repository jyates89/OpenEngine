cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(doxygen-test)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)

add_executable(${PROJECT_NAME}
    DoxygenTest.cpp)
set_target_options(${PROJECT_NAME})

if(CMAKE_VERBOSE)
    print_configuration_output(${PROJECT_NAME})
    write_generator_output(${PROJECT_NAME})
endif()
