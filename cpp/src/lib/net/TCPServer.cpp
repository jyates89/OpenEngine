//
// Created by jyates on 5/7/19.
//

#include "StandardDefines.h"
#include "net/TCPServer.h"
#include "net/TCPSocket.h"

TCPServer::TCPServer() :
    SocketServer(
            ServerType::TCP,
            AddressFamily::ANY,
            Flags::NONE) {

    socket = std::make_unique<TCPSocket>();
}

void TCPServer::run() {

}

void TCPServer::terminate() {

}
