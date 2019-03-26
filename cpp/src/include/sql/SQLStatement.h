/*
 * SQLStatement.h
 *
 *  Created on: Jul 1, 2017
 *      Author: jyates
 */

#ifndef TYPES_SQL_SQLSTATEMENT_H_
#define TYPES_SQL_SQLSTATEMENT_H_

#include <memory> // std::unique_ptr
#include <string> // std::string

#include "SQL.h"

#include "../../Patterns/Decorator.h"

class SQLStatement {
public:
    SQLStatement();
    ~SQLStatement();

    void        createStatement(std::unique_ptr<SQL> statement);
    std::string statement      () const;

private:
    std::string m_statement;
    std::unique_ptr<SQL> m_statementDecorator;

};

#endif /* TYPES_SQL_SQLSTATEMENT_H_ */
