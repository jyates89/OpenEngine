include(${CMAKE_SOURCE_DIR}/cmake/common_defines.cmake)

# https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
function(init_submodules)
    find_package(Git)
    if(GIT_FOUND)
        set(GIT_ARGUMENTS "submodule" "update" "--init" "--checkout")
        execute_process(COMMAND ${GIT_EXECUTABLE} ${GIT_ARGUMENTS}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMODULE_RESULT)

        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR
                "${GIT_EXECUTABLE} ${GIT_ARGUMENTS} failed with ${GIT_SUBMODULE_RESULT}")
        endif()
    endif()
endfunction()


################################################################################
## set_target_options(): Set usual options for the given target.
##
##  CURRENT_TARGET_NAME: name of the target to set options on.
##
################################################################################
function(set_target_options CURRENT_TARGET_NAME)
    target_include_directories(${CURRENT_TARGET_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

    target_link_libraries(${CURRENT_TARGET_NAME}
        PUBLIC  $<$<CONFIG:DEBUG>:unwind>
                $<$<CONFIG:DEBUG>:dl>)

    target_compile_definitions(${CURRENT_TARGET_NAME}
        PRIVATE $<$<CONFIG:RELEASE>:NDEBUG>)

    target_compile_options(${CURRENT_TARGET_NAME}
        ${COMMON_COMPILE_FLAGS})

    target_compile_features(${CURRENT_TARGET_NAME}
        PRIVATE ${COMMON_COMPILE_FEATURES})
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
