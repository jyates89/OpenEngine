cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(OpenEngine)

# Download doxygen to be used if it not aleady available
find_program(DOXYGEN doxygen)
if (NOT DOXYGEN)
    file(DOWNLOAD https://github.com/doxygen/doxygen/archive/Release_1_8_14.tar.gz
         ${CMAKE_BINARY_DIR}/vendor/doxygen/Doxygen_Release_1_8_14.tar.gz
         STATUS DOWNLOAD_STATUS
         )
endif()


# Provides targets: gmock and gtest
add_subdirectory(vendor/google/googletest)

enable_testing()

add_subdirectory(spike/google-mock-test)
