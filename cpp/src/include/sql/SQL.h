/*
 * SQL.h
 *
 *  Created on: Jul 1, 2017
 *      Author: jyates
 */

#ifndef TYPES_SQL_SQL_H_
#define TYPES_SQL_SQL_H_

#include <string>

#include "../../Patterns/Decorator.h"

class SQL : public Decorator<std::string> {
public:
    SQL() {}
    virtual ~SQL() {}
};

#endif /* TYPES_SQL_SQL_H_ */
