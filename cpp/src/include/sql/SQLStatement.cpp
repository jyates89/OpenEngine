/*
 * SQLStatement.cpp
 *
 *  Created on: Jul 1, 2017
 *      Author: jyates
 */

#include "SQLStatement.h"

#include <utility>

SQLStatement::SQLStatement() :
    m_statementDecorator(nullptr) {
}

SQLStatement::~SQLStatement() {
}

void SQLStatement::createStatement(std::unique_ptr<SQL> statement) {
    m_statementDecorator = std::move(statement);
    m_statementDecorator->processDecorations(m_statement);
}

std::string SQLStatement::statement() const {
    return m_statement;
}
