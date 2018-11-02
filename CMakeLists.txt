cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(OpenEngine)

execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(REVISION "${GIT_BRANCH}-${GIT_COMMIT_HASH}")
message(STATUS "Current revision = '${REVISION}'")

set(LOGO_LOCATION "${CMAKE_SOURCE_DIR}/resources/oe_logo_50x50.png")

include(ExternalProject)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
message(STATUS "Modules paths: ${CMAKE_MODULE_PATH}")
include(dependency_management)
init_submodules()

include(common_functions)
link_directories(${CMAKE_BINARY_DIR}/lib)

include(TestForSTDNamespace)
include(ProcessorCount)
ProcessorCount(PROC_COUNT)
message(STATUS "This machine has ${PROC_COUNT} cores.")

# include(GoogleTest)?
include(GNUInstallDirs)
include(GetPrerequisites)
#

# Doxygen and graphviz must be handled with ExternalProject as the
# CMakeLists.txt they use doesn't make use of CMAKE_CURRENT_SOURCE_DIR.
# Requires libtool, autoconf, automake.
option(GENERATE_DOCS "Generate documentation" ON)
if(GENERATE_DOCS)
    find_package(Graphviz)
    if (NOT GRAPHVIZ_FOUND)
        message(STATUS
            "Failed to find Graphviz CMake package... "
            "Checking for binary in path...")

        find_program(DOT_EXECUTABLE dot)
        if (NOT DOT_EXECUTABLE)
            message(STATUS "Loading ExternalProject for Graphviz.")
            ExternalProject_Add(Graphviz
                SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/graphviz
                INSTALL_DIR ${CMAKE_BINARY_DIR}
                CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
        else()
            add_custom_target(Graphviz
                ${DOT_EXECUTABLE}
                COMMENT "Dot target generated from result "
                "of find program."
                VERBATIM)
        endif()
    endif()

    find_package(Doxygen)
    if (NOT DOXYGEN_FOUND)
        message(STATUS
            "Failed to find Doxygen CMake package... "
            "Checking for binary in path...")

        find_program(DOXYGEN_EXECUTABLE doxygen)
        if (NOT DOXYGEN_EXECUTABLE)
            message(STATUS "Loading ExternalProject for Doxygen.")

            ExternalProject_Add(Doxygen
                DEPENDS Graphviz
                SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/doxygen
                INSTALL_DIR ${CMAKE_BINARY_DIR}
                CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
            set(DOXYGEN_EXECUTABLE "${CMAKE_BINARY_DIR}/bin/doxygen")
        else()
            add_custom_target(Doxygen
                ${DOXYGEN_EXECUTABLE}
                COMMENT "Doxygen target generated from result "
                        "of find program."
                VERBATIM)
        endif()
    endif()

    if (TARGET Doxygen)
        configure_file(${CMAKE_SOURCE_DIR}/config/Doxyfile.in ${CMAKE_BINARY_DIR}/config/Doxyfile)
        add_custom_target(docs ALL
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/config/Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
            COMMENT "Generating documentation."
            DEPENDS Doxygen)
    endif()
endif()
# Provides targets: gmock and gtest
add_subdirectory(vendor/google/googletest)

enable_testing()

add_subdirectory(spike/google-mock-test)
add_subdirectory(spike/doxygen-test)
