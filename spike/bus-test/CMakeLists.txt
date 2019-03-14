cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(bus-test)

add_executable(${PROJECT_NAME}
    BusTest.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/message-bus/MessageBus.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/message-bus/AsyncMessageBus.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/message-bus/SyncMessageBus.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/unique-identifiers/UniqueID.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE uuid)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

include(${CMAKE_SOURCE_DIR}/cmake/common_include.cmake)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)
if(CMAKE_VERBOSE)
    print_configuration_output(${PROJECT_NAME})
    write_generator_output(${PROJECT_NAME})
endif()
