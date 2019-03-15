/*
 * UniqueID.h
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#ifndef TYPES_UNIQUEID_H_
#define TYPES_UNIQUEID_H_

#include <string>
#include <functional>

#include <cstdint>

#include <uuid/uuid.h>

class UniqueID {
    friend class UniqueIDHasher;
public:
    enum {
        UNIQUE_ID_STR_LEN = 38
    };

    UniqueID();
    UniqueID(const UniqueID& right);

    UniqueID& operator =(const UniqueID& right);

    ~UniqueID();

    bool operator  <(const UniqueID& right) const;
    bool operator  >(const UniqueID& right) const;
    bool operator ==(const UniqueID& right) const;
    bool operator !=(const UniqueID& right) const;

    std::string getIdentifierStr() const;

private:
    uuid_t m_identifier;
    char   m_identifierStr[UNIQUE_ID_STR_LEN];

    void copy(const UniqueID& right);
};

/* We need to provide a hash specialization, so that UniqueID can be used as
 * a key in maps.
 * NOTE: follow the below link for more information (specifically the example
 * code shown at the bottom of the page).
 *
 * http://en.cppreference.com/w/cpp/container/unordered_map/unordered_map
 * */
namespace std {
    template<> struct hash<UniqueID> {
        std::size_t operator()(const UniqueID& identifier) const {
            return std::hash<std::string>{}(identifier.getIdentifierStr());
        }
    };
}

#endif /* TYPES_UNIQUEID_H_ */
