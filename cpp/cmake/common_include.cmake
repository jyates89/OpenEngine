include(${CMAKE_SOURCE_DIR}/cmake/common_defines.cmake)

if(TARGET ${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME}
            PRIVATE ${CMAKE_SOURCE_DIR}/src/include
            )

    target_link_libraries(${PROJECT_NAME}
            PUBLIC debug unwind
            )

    target_link_libraries(${PROJECT_NAME}
            PUBLIC debug dl
            )

    target_compile_definitions(${PROJECT_NAME}
            PRIVATE $<$<CONFIG:RELEASE>:NDEBUG>
            )

    target_compile_options(${PROJECT_NAME}
            ${COMMON_COMPILE_FLAGS}
            )

    target_compile_features(${PROJECT_NAME}
            PRIVATE ${COMMON_COMPILE_FEATURES}
            )


    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

else()
    message(WARNING "No targets defined prior to using the "
            "'common_include.cmake' file! Please be sure to "
            "define a target using 'add_library' or by "
            "using 'add_executable' BEFORE calling 'include()' "
            "on 'common_include.cmake'. Assign the target name "
            "to the variable 'CURRENT_TARGET_NAME'.")
endif()
