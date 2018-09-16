################################################################################
## check_deps():    Given a list of dependencies, verify that they are all
##                  available on the current system.
##
##      DEP_LIST:   This is the list of arguments; note that it MUST be passed
##                  in quotes if it is a list containing more than one item.
################################################################################
function(check_dependencies)

    # Options are flags that can be passed to the function.
    set(OPTIONS NONE)
    # One-value-keywords are options that are followed with a single value.
    set(ONE_VALUE_KEYWORDS
        DEPENDENCY_NAME)
    # Multi-value-keywords are options that can be followed with one or more values.
    set(MULTI_VALUE_KEYWORDS NONE)

    cmake_parse_arguments(OPTS
            "${OPTIONS}" "${ONE_VALUE_KEYWORDS}"
            "${MULTI_VALUE_KEYWORDS}" ${ARGN})

    foreach(LIBRARY ${DEP_LIST})
        message(STATUS "\tSearching for required library "
                "'${LIBRARY}'...")
        find_package(${LIBRARY})
        find_library(${LIBRARY}_RESULT ${LIBRARY})
        # find_library stores the result in a new cached variable
        # called <VAR>_RESULT, so we can just check that to see if
        # the variable was found.
        if (NOT ${LIBRARY}_RESULT)
            message(STATUS "${LIBRARY} is not available on this system, please"
                    " install it and attempt to run cmake again.")
            message(FATAL_ERROR "Failed to find required "
                    "library '${LIBRARY}'.")
        else()
            message(STATUS "\t\tFound the library '${LIBRARY}' at "
                    "location '${${LIBRARY}_RESULT}'.")
        endif()
    endforeach()
endfunction()

################################################################################
## print_configuration_output(): Given a target, print all useful properties.
##
##      TARGET_NAME: A target added via add_library or add_executable. This
##                   can only be called AFTER the add is completed.
################################################################################
include(${CMAKE_SOURCE_DIR}/cmake/property_list.cmake)
function(print_configuration_output TARGET_NAME)
    message("-------------------------------------")
    message(STATUS "Debug information for target '${TARGET_NAME}':")
    foreach(PROPERTY ${PROPERTY_LIST})
        get_target_property(RESULT ${TARGET_NAME} "${PROPERTY}")
        if (RESULT)
            message(STATUS "Property '${PROPERTY}' result for '${TARGET_NAME}':")
            foreach(RESULT_ENTRY ${RESULT})
                message(STATUS "\t\tValue = '${RESULT_ENTRY}'")
            endforeach()
        endif()
    endforeach()
endfunction()

################################################################################
## write_generator_output(): Given a target, print all useful properties to
##                           a file in the CMake binary directory for that
##                           target.
##
##      TARGET_NAME: A target added via add_library or add_executable. This
##                   can only be called AFTER the add is completed.
################################################################################
function(write_generator_output TARGET_NAME)
    message(STATUS "Generating generation-time debug output for: '${TARGET_NAME}'.")
    foreach(PROPERTY ${PROPERTY_LIST})
        file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_${PROPERTY}.txt"
            CONTENT "$<JOIN:$<TARGET_PROPERTY:${TARGET_NAME},${PROPERTY}>,\n>\n"  )
    endforeach()
endfunction()
