/*
 * Observer.cpp
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#include "patterns/Observer.h"

Observer::Observer() {}

Observer::~Observer() {}

const UniqueID& Observer::getIdentifier() const {
    return m_identifier;
}
