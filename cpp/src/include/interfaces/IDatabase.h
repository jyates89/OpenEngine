/*
 * IDatabase.h
 *
 *  Created on: Jun 23, 2017
 *      Author: jyates
 */

#ifndef INTERFACES_IDATABASE_H_
#define INTERFACES_IDATABASE_H_

#include <string>
#include <vector>

#include <cstddef>

class IDatabase {
public:
    typedef std::vector<std::string> Row;
    typedef std::vector<std::string> Column;
    typedef std::vector<Row> Table;

    IDatabase() {}
    virtual ~IDatabase() {}

    virtual void connect(const std::string& database) = 0;
    virtual void connect(const std::string& host, const std::string& database,
                         const std::string& user, const std::string& password) = 0;

    virtual void disconnect() = 0;

    virtual void createDatabase (const std::string& database) = 0;
    virtual void destroyDatabase(const std::string& database) = 0;

    virtual Table       getTable      (const std::string& table) = 0;

    virtual std::size_t getRowCount   (const std::string& table) = 0;
    virtual std::size_t getColumnCount(const std::string& table) = 0;

    virtual Row         getRow        (const std::string& table,
                                       std::size_t row) = 0;

    virtual Column      getColumn     (const std::string& table,
                                       std::size_t column) = 0;

    virtual std::string getEntry      (const std::string& table,
                                       std::size_t row,
                                       std::size_t column) = 0;

    virtual void createTable          () = 0;
    virtual void deleteTable          () = 0;

    virtual void insertRecord         () = 0;
    virtual void updateRecord         () = 0;
    virtual void deleteRecord         () = 0;
    virtual void obtainRecord         () = 0;

};

#endif /* INTERFACES_IDATABASE_H_ */
