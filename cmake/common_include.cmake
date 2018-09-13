include(${CMAKE_SOURCE_DIR}/common_defines.cmake)

if(TARGET ${CURRENT_TARGET_NAME})
    target_include_directories(${CURRENT_TARGET_NAME}
            PRIVATE ${CMAKE_SOURCE_DIR}/src/include
            )

    target_link_libraries(${CURRENT_TARGET_NAME}
            PUBLIC debug unwind
            )

    target_link_libraries(${CURRENT_TARGET_NAME}
            PUBLIC debug dl
            )

    target_compile_definitions(${CURRENT_TARGET_NAME}
            PRIVATE $<$<CONFIG:RELEASE>:NDEBUG>
            )

    target_compile_options(${CURRENT_TARGET_NAME}
            ${COMMON_COMPILE_FLAGS}
            )

    target_compile_features(${CURRENT_TARGET_NAME}
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
