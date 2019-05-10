cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(open-engine-testing)

include(${CMAKE_SOURCE_DIR}/cmake/common_functions.cmake)

add_executable(MessageBusTesting
    message-bus/MessageBusTest.cpp)
set_target_options(MessageBusTesting)
target_link_libraries(MessageBusTesting PRIVATE general gmock)
add_test(NAME MessageBusTesting
    COMMAND MessageBusTesting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(CommandTesting
    patterns/CommandTest.cpp)
set_target_options(CommandTesting)
target_link_libraries(CommandTesting PRIVATE general gmock)
add_test(NAME CommandTesting
    COMMAND CommandTesting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(ObserverTesting
    patterns/ObserverTest.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/UniqueID.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/patterns/Observer.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/patterns/Observable.cpp)
set_target_options(ObserverTesting)
target_link_libraries(ObserverTesting PRIVATE general gmock uuid)
add_test(NAME ObserverTesting
    COMMAND ObserverTesting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(DecoratorTesting
    patterns/DecoratorTest.cpp)
set_target_options(DecoratorTesting)
target_link_libraries(DecoratorTesting PRIVATE general gmock)
add_test(NAME DecoratorTesting
    COMMAND DecoratorTesting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(FlyweightTesting
    patterns/FlyweightTest.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/UniqueID.cpp)
set_target_options(FlyweightTesting)
target_link_libraries(FlyweightTesting PRIVATE general gmock uuid)
add_test(NAME FlyweightTesting
    COMMAND FlyweightTesting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(NetTesting
    net/SocketTest.cpp
    ${CMAKE_SOURCE_DIR}/src/lib/net/TCPServer.cpp)
set_target_options(NetTesting)
target_link_libraries(NetTesting PRIVATE general gmock)
add_test(NAME NetTesting
    COMMAND NetTesting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
