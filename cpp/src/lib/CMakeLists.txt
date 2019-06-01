
add_library(liboenet
    net/BroadcastClient.cpp
    net/BroadcastReceiver.cpp
    net/BroadcastServer.cpp
    net/TCPClient.cpp
    net/TCPServer.cpp
    net/TCPSocket.cpp
    net/UDPSocket.cpp
    net/UnicastClient.cpp
    net/UnicastReceiver.cpp
    net/UnixClient.cpp
    net/UnixServer.cpp
    net/UnixSocket.cpp
    net/Helpers.cpp)
set_target_options(liboenet)
