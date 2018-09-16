cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(OpenEngine)

# Provides targets: gmock and gtest
add_subdirectory(vendor/google/googletest)

add_subdirectory(spike/google-mock-test)
