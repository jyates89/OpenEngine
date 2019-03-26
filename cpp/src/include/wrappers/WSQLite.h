/*
 * WSQLite.h
 *
 *  Created on: Jun 23, 2017
 *      Author: jyates
 */

#ifndef WRAPPERS_WSQLITE_H_
#define WRAPPERS_WSQLITE_H_

#include "../Types/StandardDefines.h"
#include "../Interfaces/IDatabase.h"

extern "C" {
#include "sqlite3.h"
}

class WSQLite : public IDatabase {
public:
    WSQLite();
    virtual ~WSQLite();

    virtual void connect(const std::string& database);
    virtual void connect(const std::string& host, const std::string& database,
                         const std::string& user, const std::string& password);

    virtual void disconnect();

    virtual void createDatabase (const std::string& database);
    virtual void destroyDatabase(const std::string& database);

    virtual Table       getTable      (const std::string& table);

    virtual std::size_t getRowCount   (const std::string& table);
    virtual std::size_t getColumnCount(const std::string& table);

    virtual Row         getRow        (const std::string& table,
                                       std::size_t row);

    virtual Column      getColumn     (const std::string& table,
                                       std::size_t column);

    virtual std::string getEntry      (const std::string& table,
                                       std::size_t row,
                                       std::size_t column);
private:
    sqlite3* m_sqlHandle;

    static const std::string OPEN_ERROR;
    static const std::string CLOSE_ERROR;
    static const std::string EXEC_ERROR;
};

inline WSQLite::WSQLite() :
    m_sqlHandle(nullptr) {
}

inline WSQLite::~WSQLite() {
}

#endif /* WRAPPERS_WSQLITE_H_ */
