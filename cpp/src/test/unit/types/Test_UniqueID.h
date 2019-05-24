/*
 * Test_UniqueID.h
 *
 *  Created on: Jun 5, 2017
 *      Author: jyates
 */

#ifndef TESTING_TYPES_TEST_UNIQUEID_H_
#define TESTING_TYPES_TEST_UNIQUEID_H_

#include <sstream>
#include <cxxtest/TestSuite.h>

#include "../Types/UniqueID.h"

class Test_UniqueID: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testUniqueID() {
        UniqueID firstID, secondID;
        TS_ASSERT(firstID != secondID);

        std::stringstream firstUniqueStr("First unique identifier: ");
        firstUniqueStr << firstID.getIdentifierStr();
        TS_TRACE(firstUniqueStr.str().c_str());

        std::stringstream secondUniqueStr("Second unique identifier: ");
        secondUniqueStr << secondID.getIdentifierStr();
        TS_TRACE(secondUniqueStr.str().c_str());
    }

private:

};

#endif // TESTING_TYPES_TEST_UNIQUEID_H_
