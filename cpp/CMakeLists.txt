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

# * Grab the current version from the last line in the
#   version history.
FILE(STRINGS "version_history.txt" VERSION_HISTORY)
FOREACH(VERSION_LINE ${VERSION_HISTORY})
    SET(CURRENT_VERSION ${VERSION_LINE})
ENDFOREACH()
MESSAGE(STATUS "Current version: ${CURRENT_VERSION}-${REVISION}")
STRING(REGEX MATCHALL "[0-9]+|[A-Z]+"
    VERSION_SEGMENTS ${CURRENT_VERSION})
LIST(GET VERSION_SEGMENTS 0 VERSION_MAJOR)
LIST(GET VERSION_SEGMENTS 1 VERSION_MINOR)
LIST(GET VERSION_SEGMENTS 2 VERSION_PATCH)
LIST(LENGTH VERSION_SEGMENTS VERSION_SEGMENT_LEN)
IF(VERSION_SEGMENT_LEN GREATER 3)
    LIST(GET VERSION_SEGMENTS 3 REL_DESIGNATION)
ENDIF()

# * Handle cases where we want to increase the version number
#   or change the release designation.
#   Usage (shown separately, but may be used together):
#       cmake -DREV_MAJOR=TRUE ..
#       cmake -DREV_MINOR=TRUE ..
#       cmake -DREV_PATCH=TRUE ..
#       cmake -DCHANGE_REL_DESIGNATION=ALPHA ..
IF(REV_MAJOR OR REV_MINOR OR REV_PATCH OR REL_DESIG)
    IF(REV_MAJOR)
        MATH(EXPR NEW_VERSION_MAJOR "${VERSION_MAJOR}+1")
        SET(VERSION_MAJOR ${NEW_VERSION_MAJOR})
    ENDIF()
    IF(REV_MINOR)
        MATH(EXPR NEW_VERSION_MINOR "${VERSION_MINOR}+1")
        SET(VERSION_MINOR ${NEW_VERSION_MINOR})
    ENDIF()
    IF(REV_PATCH)
        MATH(EXPR NEW_VERSION_PATCH "${VERSION_PATCH}+1")
        SET(VERSION_PATH ${NEW_VERSION_PATCH})
    ENDIF()
    IF(REL_DESIG)
        IF(REL_DESIG STREQUAL "DISABLE")
            SET(REL_DESIGNATION "")
        ELSE()
            SET(REL_DESIGNATION ${REL_DESIG})
        ENDIF()
    ENDIF()
    FILE(APPEND "version_history.txt"
        "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${REL_DESIGNATION}\n")
    UNSET(REV_MAJOR CACHE)
    UNSET(REV_MINOR CACHE)
    UNSET(REV_PATCH CACHE)
    UNSET(REL_DESIG CACHE)
ENDIF()


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

    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/config/Doxyfile)
    add_custom_target(docs ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/config/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
        COMMENT "Generating documentation."
        DEPENDS Doxygen Graphviz GraphvizConfig)
endif()

# Provides targets: gmock and gtest
add_subdirectory(vendor/google/googletest)


# Spike Code
add_subdirectory(spike/google-mock-test)
add_subdirectory(spike/doxygen-test)

# Testing
add_subdirectory(${CMAKE_SOURCE_DIR}/src/test)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/tools)

# Libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/src/lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
