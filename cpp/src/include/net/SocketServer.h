//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_SERVER_H
#define OPENENGINE_SERVER_H

#include <netdb.h>
#include <sys/types.h>
#include <memory>

#include "net/Socket.h"

class SocketServer {
protected:
    std::unique_ptr<Socket> socket;

    enum class ServerType {
        INVALID,
        TCP,
        UNIX,
    } serverType;

    enum class AddressFamily {
        ANY = AF_UNSPEC,
        UNIX = AF_UNIX,
        IPV4 = AF_INET,
        IPV6 = AF_INET6,
    } addressFamily;

    enum class Flags {
        NONE = 0,
        IP_AUTO_FILL = AI_PASSIVE,
        RESOLVE_HOSTNAME = AI_CANONNAME,
        DISABLE_IP_RESOLUTION = AI_NUMERICHOST,
        USE_HOST_IP_CONFIG = AI_ADDRCONFIG,
        DISABLE_PORT_RESOLUTION = AI_NUMERICSERV,
    } flags;

    SocketServer(ServerType type,
                 AddressFamily family, Flags serverFlags);

    virtual void run() = 0;
    virtual void terminate() = 0;

public:
    virtual ~SocketServer() = default;
};

SocketServer::SocketServer(ServerType type,
        AddressFamily family, Flags serverFlags) :
    socket(nullptr),
    serverType(type),
    addressFamily(family),
    flags(serverFlags) {

}

#endif //OPENENGINE_SERVER_H
