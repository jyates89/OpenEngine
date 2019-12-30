//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_TCPSERVER_H
#define OPENENGINE_TCPSERVER_H

#include "TCPSocket.h"

#include <string>

namespace OE {

class TCPServer {
public:
    explicit TCPServer(std::string port);

    void run();
    void terminate();
};

}
#endif //OPENENGINE_TCPSERVER_H
