//
// Created by jyates on 6/4/19.
//

#ifndef OPENENGINE_SOCKETSETTINGS_H
#define OPENENGINE_SOCKETSETTINGS_H

#include <memory>

class SocketSettings {
public:
    SocketSettings(std::unique_ptr<SocketSettings> settings);
};

#endif //OPENENGINE_SOCKETSETTINGS_H
