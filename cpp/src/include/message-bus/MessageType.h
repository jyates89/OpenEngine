//
// Created by jyates on 2/27/19.
//

#ifndef OPENENGINE_MESSAGETYPE_H
#define OPENENGINE_MESSAGETYPE_H


#include <cstdint>
#include <string>


#include "unique-identifiers/UniqueID.h"
/*
 * Represents the basic message type for the bus. Users of the bus
 * inherit from this class and define the message type via the identifier
 * and the label.
 */
class MessageType {
    UniqueID    m_identifier;
    std::string m_messageLabel;

protected:
    explicit MessageType(std::string label)
            : m_identifier(), m_messageLabel(std::move(label)) {

    }

public:
    MessageType() = delete;
    virtual ~MessageType() = default;

    inline UniqueID identifier() const {
        return m_identifier;
    }

    inline const std::string& messageLabel() const {
        return m_messageLabel;
    }
};
#endif //OPENENGINE_MESSAGETYPE_H
