################################################################################
## check_deps():    Given a list of dependencies, verify that they are all
##                  available on the current system.
##
##      DEP_LIST:   This is the list of arguments; note that it MUST be passed
##                  in quotes if it is a list containing more than one item.
################################################################################
function(check_deps DEP_LIST)
    foreach(LIBRARY ${DEP_LIST})
        message(STATUS "\tSearching for required library "
                "'${LIBRARY}'...")
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
## print_target_debug(): Given a target, print all useful properties.
##
##      TARGET_NAME: A target added via add_library or add_executable. This
##                   can only be called AFTER the add is completed.
################################################################################
include(property_list.cmake)
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
## produce_generate_output(): Given a target, print all useful properties to
##                            a file in the CMake binary directory for that
##                            target.
##
##      TARGET_NAME: A target added via add_library or add_executable. This
##                   can only be called AFTER the add is completed.
################################################################################
function(write_generator_output TARGET_NAME)
    message(STATUS "Generating generation-time debug output for: '${TARGET_NAME}'.")
    foreach(PROPERTY ${PROPERTY_LIST})
        file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}_${PROPERTY}.txt"
            CONTENT "$<JOIN:$<TARGET_PROPERTY:${TARGET_NAME},${PROPERTY}>,\n>\n"  )
    endforeach()
endfunction()


################################################################################
## add_test_header(): Given a CxxTest header, converts the header name into a
##                    source file name, and then generates the test from the
##                    header.
##
##    TESTING_HEADER: The CxxTest header containing the unit tests.
################################################################################
function(add_test_header)
    # Options are flTESTING_HEADERags that can be passed to the function.
    set(OPTIONS NONE)
    # One-value-keywords are options that are followed with a single value.
    set(ONE_VALUE_KEYWORDS  TEST_HEADER
                            TEST_BINARY)
    # Multi-value-keywords are options that can be followed with one or more values.
    set(MULTI_VALUE_KEYWORDS DEPENDENCIES)
    cmake_parse_arguments(OPTS
            "${OPTIONS}" "${ONE_VALUE_KEYWORDS}"
            "${MULTI_VALUE_KEYWORDS}" ${ARGN})

    # the source file is generated from the header, so replace the extension
    # and save it to a new variable
    string(REPLACE ".h" ".cpp" TESTING_SOURCE ${OPTS_TEST_HEADER})

    # get the generated source file name by removing the path from the file name
    get_filename_component(TESTING_SOURCE ${TESTING_SOURCE} NAME)

    # Create the directory used to hold the generated test files.
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated)

    # NOTE: cxxtest_add_test checks the var CMAKE_RUNTIME_OUTPUT_DIRECTORY and
    # then uses add_test to configure the binary location, so we cannot set it
    # AFTER the target is created... we must set this prior to calling.
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

    # add the test (internally uses add_executable and add_test)
    cxxtest_add_test(${OPTS_TEST_BINARY} "generated/${TESTING_SOURCE}" ${OPTS_TEST_HEADER})

    # link any required libraries
    target_link_libraries(${OPTS_TEST_BINARY} PRIVATE ${OPTS_DEPENDENCIES})

    # add the include directory
    target_include_directories(${OPTS_TEST_BINARY} PRIVATE ${CXXTEST_INCLUDE_DIR})
ENDFUNCTION()
