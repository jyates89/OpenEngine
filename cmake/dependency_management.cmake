function(find_dependency)

    # Options are flags that can be passed to the function.
    set(OPTIONS
        BINARY_TYPE
        LIBRARY_TYPE
        HEADER_TYPE)

    # One-value-keywords are options that are followed with a single value.
    set(ONE_VALUE_KEYWORDS
        DEPENDENCY_NAME
        DEPENDENCY_VERSION
        RESULT_TARGET)

    # Multi-value-keywords are options that can be followed with one or more values.
    set(MULTI_VALUE_KEYWORDS DEPENDENCY_LOCATIONS)

    cmake_parse_arguments(OPTS
        "${OPTIONS}" "${ONE_VALUE_KEYWORDS}"
        "${MULTI_VALUE_KEYWORDS}" ${ARGN})

    message(STATUS "Looking for: ${OPTS_DEPENDENCY_NAME}")

    if(OPTS_BINARY_TYPE)
        message(STATUS "Type is BINARY")
        find_program(PROGRAM_RESULT
            ${OPTS_DEPENDENCY_NAME}
            HINTS ${OPTS_DEPENDENCY_LOCATIONS}
            DOC "Location for ${OPTS_DEPENDENCY_NAME}.")
        if(NOT PROGRAM_RESULT)
            message(STATUS "Failed to find ${OPTS_DEPENDENCY_NAME}.")
        else()
            message(STATUS "Found ${OPTS_DEPENDENCY_NAME} at ${PROGRAM_RESULT}.")
            set(${OPTS_DEPENDENCY_NAME}_PATH ${PROGRAM_RESULT} PARENT_SCOPE)
            add_custom_target(RESULT_TARGET)
        endif()

    elseif(OPTS_LIBRARY_TYPE)
        find_library()
        message(STATUS "Type is LIBRARY")
    elseif(OPTS_HEADER_TYPE)
        message(STATUS "Type is HEADER")
    else()
        message(STATUS "No type specified.")
    endif()

    message(STATUS "Locations provided: ${OPTS_DEPENDENCY_LOCATIONS}")

    find_package(${OPTS_DEPENDENCY_NAME} ${OPTS_DEPENDENCY_VERSION}
        HINTS ${OPTS_DEPENDENCY_LOCATIONS})
    if(${OPTS_DEPENDENCY_NAME}_FOUND)
        message(STATUS "Package ${OPTS_DEPENDENCY_NAME} found!")
    else()
        find_library(LIBRARY_RESULT ${OPTS_DEPENDENCY_NAME}
            ${OPTS_DEPENDENCY_LOCATIONS})
        if(NOT LIBRARY_RESULT)
            message(STATUS "Did NOT find the library.")
        endif()
    endif()

endfunction()


# https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
function(init_submodules)
    find_package(Git)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        set(GIT_ARGUMENTS "submodule" "init")
        execute_process(COMMAND ${GIT_EXECUTABLE} ${GIT_ARGUMENTS}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMODULE_RESULT)

        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR
                "${GIT_EXECUTABLE} ${GIT_ARGUMENTS} failed with ${GIT_SUBMODULE_RESULT}")
        endif()
    endif()
endfunction()
