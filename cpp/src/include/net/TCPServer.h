//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_TCPSERVER_H
#define OPENENGINE_TCPSERVER_H

#include "SocketServer.h"
#include "TCPSocket.h"

class TCPServer : public SocketServer {
public:
    TCPServer();
    ~TCPServer() override = default;

    void run() override;
    void terminate() override;
};
#endif //OPENENGINE_TCPSERVER_H
