/*
 * Insert.h
 *
 *  Created on: Jul 1, 2017
 *      Author: jyates
 */

#ifndef TYPES_SQL_INSERT_H_
#define TYPES_SQL_INSERT_H_

#include <string>

#include "SQL.h"

class Insert : public SQL {
public:
    enum class InsertionType {
        INSERT,
        INSERT_OR_ROLLBACK,
        INSERT_OR_ABORT,
        INSERT_OR_FAIL,
        INSERT_OR_IGNORE,
        INSERT_OR_REPLACE,
        REPLACE
    };

    Insert(InsertionType type = InsertionType::INSERT);
    ~Insert();

private:
    InsertionType m_insertionType;

    virtual void processDecoration(std::string& decoration);

};

inline Insert::Insert(InsertionType type) :
    m_insertionType(type) {
}

inline Insert::~Insert() {
}

inline void Insert::processDecoration(std::string& decoration) {
    switch (m_insertionType) {
    case InsertionType::INSERT:
        decoration.append(" INSERT ");
        break;
    case InsertionType::INSERT_OR_ROLLBACK:
        decoration.append(" INSERT OR ROLLBACK ");
        break;
    case InsertionType::INSERT_OR_ABORT:
        decoration.append(" INSERT OR ABORT ");
        break;
    case InsertionType::INSERT_OR_FAIL:
        decoration.append(" INSERT OR FAIL ");
        break;
    case InsertionType::INSERT_OR_IGNORE:
        decoration.append(" INSERT OR IGNORE ");
        break;
    case InsertionType::INSERT_OR_REPLACE:
        decoration.append(" INSERT OR REPLACE ");
        break;
    case InsertionType::REPLACE:
        decoration.append(" REPLACE ");
        break;
    default:
        break;
    }
    decoration.append(" INTO ");
}

#endif /* TYPES_SQL_INSERT_H_ */
