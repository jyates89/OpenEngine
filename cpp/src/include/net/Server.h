//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_SERVER_H
#define OPENENGINE_SERVER_H

#include <netdb.h>
#include <sys/types.h>

class Server {
public:
    enum class ServerType {
        INVALID,
        TCP,
        UNIX,
    };

    enum class AddressFamily {
        ANY = AF_UNSPEC,
        UNIX = AF_UNIX,
        IPV4 = AF_INET,
        IPV6 = AF_INET6,
    };

    enum class Flags {
        IP_FILL = AI_PASSIVE
    };

};

#endif //OPENENGINE_SERVER_H
