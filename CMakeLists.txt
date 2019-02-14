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
link_directories(${CMAKE_BINARY_DIR}/lib)

include(ExternalProject)

# Adds additional path to search for CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
message(STATUS "Modules paths: ${CMAKE_MODULE_PATH}")

include(common_functions)
init_submodules()


include(TestForSTDNamespace)
include(ProcessorCount)

ProcessorCount(PROC_COUNT)
message(STATUS "This machine can execute ${PROC_COUNT} threads concurrently.")

include(GNUInstallDirs)
include(GetPrerequisites)

include(CMakeGraphVizOptions)
#add_custom_target(GenerateDependencyTree ALL "${CMAKE_COMMAND}"
#   "--graphviz=${CMAKE_BINARY_DIR}/generated/depends.dot" "..")

option(GENERATE_DOCS "Generate documentation" ON)
if(GENERATE_DOCS)
    # Doxygen and graphviz must be handled with ExternalProject as the
    # CMakeLists.txt they use doesn't make use of CMAKE_CURRENT_SOURCE_DIR.
    # Requires libtool, autoconf, automake.

    find_program(DOXYGEN_EXECUTABLE doxygen)
    if (NOT DOXYGEN_EXECUTABLE)
        message(STATUS "Doxygen NOT found. Loading external project.")

        # Creates the target from an external project.
        ExternalProject_Add(Doxygen
            SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/doxygen
            INSTALL_DIR ${CMAKE_BINARY_DIR}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
        set(DOXYGEN_EXECUTABLE ${CMAKE_BINARY_DIR}/bin/doxygen)

    else()
        message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE}")

        # Creates the custom target from the executable we found.
        add_custom_target(Doxygen DOXYGEN_EXECUTABLE)
    endif()

    find_program(DOT_EXECUTABLE dot)
    if (NOT DOT_EXECUTABLE)
        message(STATUS "Loading external project for Graphviz to build 'dot'.")

        list(APPEND CMAKE_ARGS "-DCMAKE_INSTALL_RPATH_USE_LINK_PATH=TRUE")
        list(APPEND CMAKE_ARGS "-DCMAKE_SKIP_BUILD_RPATH=FALSE")
        list(APPEND CMAKE_ARGS "-DCMAKE_BUILD_WITH_INSTALL_RPATH=FALSE")
        list(APPEND CMAKE_ARGS "-DCMAKE_INSTALL_RPATH=${CMAKE_BINARY_DIR}/lib")
        list(APPEND CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}")
        ExternalProject_Add(Graphviz
            SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/graphviz
            INSTALL_DIR ${CMAKE_BINARY_DIR}
            CMAKE_ARGS "${CMAKE_ARGS}")

        add_custom_target(GraphvizConfig
            ${CMAKE_BINARY_DIR}/bin/dot -c
            BYPRODUCTS ${CMAKE_BINARY_DIR}/lib/config6
            DEPENDS Graphviz)

        set(DOT_EXECUTABLE ${CMAKE_BINARY_DIR}/bin/dot)

    else()
        message(STATUS "Dot found: ${DOT_EXECUTABLE}")

        add_custom_target(Graphviz DOT_EXECUTABLE)
    endif()

    configure_file(${CMAKE_SOURCE_DIR}/config/Doxyfile.in ${CMAKE_BINARY_DIR}/config/Doxyfile)
    add_custom_target(docs ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/config/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
        COMMENT "Generating documentation."
        DEPENDS Doxygen Graphviz GraphvizConfig)
endif()


# Provides targets: gmock and gtest
add_subdirectory(vendor/google/googletest)

enable_testing()

add_subdirectory(spike/google-mock-test)
add_subdirectory(spike/doxygen-test)
add_subdirectory(spike/bus-test)
