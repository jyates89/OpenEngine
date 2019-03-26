/*
 * Entry.h
 *
 *  Created on: Jul 8, 2017
 *      Author: jyates
 */

#ifndef TYPES_SQL_ENTRY_H_
#define TYPES_SQL_ENTRY_H_

#include <string>
#include <utility>

class Entry {
public:
    enum class EntryType {
        NONE,
        INTEGER,
        LONGLONG,
        STRING,
        CHAR,
        TEXT,
        FLOAT,
        DOUBLE,
        REAL,
        DATETIME,
        NUMERIC,
    };

    enum class KeyType {
        NONE,
        PRIMARY,
        FOREIGN,
    };

    Entry(std::string name,    std::string value);

    Entry(std::string name,    std::string value);

    Entry(std::string name,    std::string value,
          EntryType entryType);

    Entry(std::string name,    std::string value,
          EntryType entryType, std::string defaultVal);

    Entry(std::string name,    std::string value,
          EntryType entryType, KeyType keyType);

    Entry(std::string name, std::string value, EntryType type,
          std::string defaultVal, KeyType keyType);

    ~Entry();

    std::string name() const;
    std::string type() const;

    std::string value() const;

private:
    std::pair<std::string, std::pair<std::string, std::string>> m_entry;
};

inline Entry::Entry(std::string name, std::string value) {
    Entry(name, value, EntryType::NONE, false);
}

inline Entry::Entry(std::string name, std::string value, EntryType type) {
    Entry(name, value, type, false);
}

inline Entry::Entry(std::string name, std::string value, EntryType type,
        bool isPrimaryKey) {
    m_entry.first = name;
    m_entry.second.first  = convertTypetoStr(type);
    m_entry.second.second = value;
}

inline Entry::Entry(std::string name, std::string value, EntryType type,
        std::string defaultVal) {
}

inline Entry::~Entry() {
}

inline std::string Entry::name() const {
    return m_entry.first;
}

inline std::string Entry::type() const {
    return m_entry.second.first;
}

inline std::string Entry::value() const {
    return m_entry.second.second;
}

inline Entry::Entry(std::string name, std::string value, EntryType entryType,
        KeyType keyType) {
}

inline Entry::Entry(std::string name, std::string value, EntryType type,
        std::string defaultVal, KeyType keyType) {
    m_entry.first = name;
    switch(type) {
    case EntryType::INTEGER:
        m_entry.second.first = "INTEGER";
        break;
    case EntryType::LONGLONG:
        m_entry.second.first = "BIGINT";
        break;
    case EntryType::STRING:
    case EntryType::CHAR:
    case EntryType::TEXT:
        m_entry.second.first = "TEXT";
        break;
    case EntryType::FLOAT:
    case EntryType::DOUBLE:
    case EntryType::REAL:
        m_entry.second.first = "REAL";
        break;
    case EntryType::DATETIME:
    case EntryType::NUMERIC:
        m_entry.second.first = "NUMERIC";
        break;
    default:
        m_entry.second.first = "NONE";
    }
}

#endif /* TYPES_SQL_ENTRY_H_ */
