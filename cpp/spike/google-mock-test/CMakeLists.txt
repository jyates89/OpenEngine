cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(google-mock-test)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)

add_executable(${PROJECT_NAME} GoogleMockTest.cpp)
set_target_options(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE general gmock)

if(CMAKE_VERBOSE)
    print_configuration_output(${PROJECT_NAME})
    write_generator_output(${PROJECT_NAME})
endif()

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
