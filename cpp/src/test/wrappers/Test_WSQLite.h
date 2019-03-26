/*
 * Test_WSQLite.h
 *
 *  Created on: Jun 24, 2017
 *      Author: jyates
 */

#ifndef TESTING_WRAPPERS_TEST_WSQLITE_H_
#define TESTING_WRAPPERS_TEST_WSQLITE_H_

#include <string>

#include <sstream>
#include <cxxtest/TestSuite.h>

#include "WSQLite.h"

class Test_WSQLite: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testCreateDestroy() {
//        WSQLite sqliteHandle;
//
//        sqliteHandle.createDatabase(m_databaseName);
//
//        sqliteHandle.destroyDatabase(m_databaseName);
    }

private:
    std::string m_hostName;
    std::string m_databaseName;
    std::string m_userName;
    std::string m_password;
};

#endif // TESTING_WRAPPERS_TEST_WSQLITE_H_
