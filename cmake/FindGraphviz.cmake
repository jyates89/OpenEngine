    find_program(DOT_EXECUTABLE dot PATHS "${CMAKE_BINARY_DIR}")
    if (NOT DOT_EXECUTABLE)
        message(STATUS "Loading ExternalProject for Graphviz.")
        ExternalProject_Add(Graphviz
            SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/graphviz
            INSTALL_DIR ${CMAKE_BINARY_DIR}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
    else()
        message(STATUS "Found dot executable: ${DOT_EXECUTABLE}")
        add_custom_target(Graphviz
            ${DOT_EXECUTABLE}
            COMMENT "Dot target generated from result "
            "of find program."
            VERBATIM)
    endif()
