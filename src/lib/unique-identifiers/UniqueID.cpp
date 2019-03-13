/*
 * UniqueID.cpp
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#include "../../include/unique-identifiers/UniqueID.h"

#include <cstring>
#include <stdexcept>

UniqueID::UniqueID() {
    uuid_generate(m_identifier);
    uuid_unparse(m_identifier, m_identifierStr);
}

UniqueID::UniqueID(const UniqueID& right) {
    if (this != &right) {
        copy(right);
    }
}

UniqueID& UniqueID::operator=(const UniqueID& right) {
    if (this != &right) {
        copy(right);
    }
    return *this;
}

UniqueID::~UniqueID() {

}

bool UniqueID::operator<(const UniqueID& right) const {
    return uuid_compare(m_identifier, right.m_identifier) < 0;
}

bool UniqueID::operator>(const UniqueID& right) const {
    return uuid_compare(m_identifier, right.m_identifier) > 0;
}

bool UniqueID::operator==(const UniqueID& right) const {
    return uuid_compare(m_identifier, right.m_identifier) == 0;
}

bool UniqueID::operator!=(const UniqueID& right) const {
    return uuid_compare(m_identifier, right.m_identifier) != 0;
}

std::string UniqueID::getIdentifierStr() const {
    return m_identifierStr;
}

void UniqueID::copy(const UniqueID& right) {
    uuid_copy(m_identifier, right.m_identifier);
    std::strncpy(m_identifierStr, right.m_identifierStr,
            UNIQUE_ID_STR_LEN);
}
