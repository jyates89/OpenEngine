//
// Created by jyates on 5/4/19.
//

#ifndef OPENENGINE_DESERIALIZABLE_H
#define OPENENGINE_DESERIALIZABLE_H

#include <vector>

// Deserializable Interface
class Deserializable {
public:
    virtual void deserialize(const std::vector<unsigned char>& data) = 0;
};
#endif //OPENENGINE_DESERIALIZABLE_H
