cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(OpenEngine)


include(ExternalProject)

find_program(DOXYGEN_RESULT doxygen REQUIRED)
find_program(DOT_RESULT dot)
if(NOT DOXYGEN_RESULT OR NOT DOT_RESULT)
    # Doxygen and graphviz must be handled with ExternalProject as the
    # CMakeLists.txt they use doesn't make use of CMAKE_CURRENT_SOURCE_DIR.
    # Requires libtool, autoconf, automake.
    ExternalProject_Add(Graphviz
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/graphviz
        PREFIX ${CMAKE_BINARY_DIR}/vendor/graphviz
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/vendor/graphviz)

    ExternalProject_Add(Doxygen
        DEPENDS Graphviz
        PREFIX ${CMAKE_BINARY_DIR}/vendor/doxygen
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/doxygen
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/vendor/doxygen)

endif()



# Provides targets: gmock and gtest
add_subdirectory(vendor/google/googletest)

enable_testing()

add_subdirectory(spike/google-mock-test)
add_subdirectory(spike/doxygen-test)
