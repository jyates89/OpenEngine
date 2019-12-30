//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_TCPCLIENT_H
#define OPENENGINE_TCPCLIENT_H

#include "StandardDefines.h"
#include "TCPSocket.h"

#include <string>
#include <memory>

namespace OE {

class TCPClient {
public:
private:

    std::string hostname;
    std::string port;
};

}

#endif //OPENENGINE_TCPCLIENT_H
