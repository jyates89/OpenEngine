/*
 * WSQLite.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: jyates
 */

#include "WSQLite.h"

#include <stdexcept>

void WSQLite::connect(const std::string& database) {
    if (m_sqlHandle != nullptr) {
        disconnect();
    }
    if (sqlite3_open(database.c_str(), &m_sqlHandle) != SQLITE_OK) {
        throw std::runtime_error(OPEN_ERROR + sqlite3_errmsg(m_sqlHandle));
    }
}

void WSQLite::connect(const std::string& host, const std::string& database,
        const std::string& user, const std::string& password) {
    connect(database);
}

void WSQLite::disconnect() {
    if (sqlite3_close(m_sqlHandle) != SQLITE_OK) {
        throw std::runtime_error(CLOSE_ERROR + sqlite3_errmsg(m_sqlHandle));
    }
    m_sqlHandle = nullptr;
}

void WSQLite::createDatabase(const std::string& database) {
    throw std::runtime_error("not implemented");
}

void WSQLite::destroyDatabase(const std::string& database) {
    throw std::runtime_error("not implemented");
}

WSQLite::Table WSQLite::getTable(const std::string& table) {
    return WSQLite::Table();
}

std::size_t WSQLite::getRowCount(const std::string& table) {
    return 0;
}

std::size_t WSQLite::getColumnCount(const std::string& table) {
    return 0;
}

WSQLite::Row WSQLite::getRow(const std::string& table, std::size_t row) {
    return WSQLite::Row();
}

WSQLite::Column WSQLite::getColumn(const std::string& table, std::size_t column) {
    return WSQLite::Column();
}

std::string WSQLite::getEntry(const std::string& table, std::size_t row,
        std::size_t column) {
    return "";
}

const std::string WSQLite::OPEN_ERROR  = "failed to open database connection: ";
const std::string WSQLite::CLOSE_ERROR = "failed to close database connection: ";
const std::string WSQLite::EXEC_ERROR  = "failed to execute SQL statement: ";
