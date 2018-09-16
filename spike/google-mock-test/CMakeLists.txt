cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(google-mock-test)

add_executable(${PROJECT_NAME} GoogleMockTest.cpp)
target_link_libraries(${PROJECT_NAME} gmock)
