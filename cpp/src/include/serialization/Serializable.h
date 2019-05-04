//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_SERIALIZABLE_H
#define OPENENGINE_SERIALIZABLE_H

#include <vector>

// Serializable Interface
class Serializable {
public:
    virtual std::vector<unsigned char> serialize() = 0;
};

#endif //OPENENGINE_SERIALIZABLE_H
