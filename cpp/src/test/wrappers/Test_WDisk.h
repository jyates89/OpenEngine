/*
 * Test_WDisk.h
 *
 *  Created on: Jun 26, 2017
 *      Author: jyates
 */

#ifndef TESTING_WRAPPERS_TEST_WDISK_H_
#define TESTING_WRAPPERS_TEST_WDISK_H_

#include <string>
#include <algorithm>

#include <sstream>
#include <cxxtest/TestSuite.h>

#include <ctime>

#include "Wrappers/WDisk.h"

class Test_WDisk: public CxxTest::TestSuite {
public:
    Test_WDisk();
    ~Test_WDisk();

    void setUp();
    void tearDown();

    void testTouchModified();
    void testWriteReadString();
    void testWriteReadVector();
    void testWriteReadData();
    void testSeekFileSmall();
    void testSeekFileBig();
    void testBlockSize();
    void testCreatePath();
    void testListPath();
    void testFailure();

private:
    std::string m_fileName;
};

inline Test_WDisk::Test_WDisk() :
    m_fileName("testFile.txt") {
}

inline Test_WDisk::~Test_WDisk() {
}

inline void Test_WDisk::setUp() {
}

inline void Test_WDisk::tearDown() {
}

inline void Test_WDisk::testTouchModified() {
    WDisk disk;
    disk.touchFile(m_fileName);
    TS_ASSERT(disk.pathExists(m_fileName));
    sleep(1);
    disk.touchFile(m_fileName);
    std::chrono::time_point<std::chrono::system_clock> now =
            std::chrono::system_clock::now();
    std::chrono::seconds epoch = std::chrono::duration_cast<std::chrono::seconds>(
                       now.time_since_epoch());
    TS_ASSERT(disk.lastModified(m_fileName) == epoch);
    disk.remove(m_fileName);
}


inline void Test_WDisk::testWriteReadString() {
    std::string string = "The quick brown fox jumps over the lazy dog.\n";

    WDisk disk;
    disk.openFile(m_fileName, "w");
    disk.write(string);
    disk.closeFile();

    disk.openFile(m_fileName, "r");
    TS_ASSERT_EQUALS(string, disk.read<std::string>());
    disk.closeFile();
    disk.remove(m_fileName);

    TS_ASSERT_EQUALS(string.length(), disk.operationStats().first  /* write */);
    TS_ASSERT_EQUALS(string.length(), disk.operationStats().second /* read  */)
}

inline void Test_WDisk::testWriteReadVector() {
    std::string string = "The quick brown fox jumps over the lazy dog.\n";
    std::vector<std::string> stringVector;

    WDisk disk;

    const std::size_t count = 5000;
    std::size_t index = 0;
    while (index++ < count) {
        stringVector.push_back(string);
    }

    disk.openFile(m_fileName, "w");
    disk.write(stringVector);
    disk.closeFile();

    disk.openFile(m_fileName, "r");
    TS_ASSERT_EQUALS(disk.read<std::vector<std::string>>(), stringVector);
    disk.closeFile();
    disk.remove(m_fileName);

    TS_ASSERT_EQUALS(string.length() * count, disk.operationStats().first  /* write */);
    TS_ASSERT_EQUALS(string.length() * count, disk.operationStats().second /* read  */);
}

inline void Test_WDisk::testWriteReadData() {
    std::vector<std::uint8_t> dataVector = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    WDisk disk;

    disk.openFile(m_fileName, "wb");
    disk.write(dataVector);
    disk.closeFile();

    disk.openFile(m_fileName, "rb");
    TS_ASSERT_EQUALS(disk.read<std::vector<std::uint8_t>>(), dataVector);
    disk.closeFile();
    disk.remove(m_fileName);

    TS_ASSERT_EQUALS(dataVector.size(), disk.operationStats().first  /* write */);
    TS_ASSERT_EQUALS(dataVector.size(), disk.operationStats().second /* read  */);

}

inline void Test_WDisk::testSeekFileSmall() {
    std::vector<std::uint8_t> dataVector;

    WDisk disk;

    const std::size_t count = 255;
    std::size_t index = 0;
    while (index++ < count) {
        dataVector.push_back(static_cast<std::uint8_t>(index));
    }

    disk.openFile(m_fileName, "wb");
    disk.write(dataVector);
    disk.closeFile();

    std::vector<std::uint8_t> offsetVector(dataVector.begin() + 10, dataVector.end());

    disk.openFile(m_fileName, "rb");
    TS_ASSERT_EQUALS(offsetVector, disk.read<std::vector<std::uint8_t>>(10));
    disk.closeFile();

    TS_ASSERT_EQUALS(dataVector.size(), disk.operationStats().first  /* write */);
    TS_ASSERT_EQUALS(offsetVector.size(), disk.operationStats().second /* read  */);
}

inline void Test_WDisk::testSeekFileBig() {
    std::vector<std::uint8_t> dataVector;

    WDisk disk;

    const std::size_t count = 4106;
    std::size_t index = 0;
    while (index++ < count) {
        dataVector.push_back(static_cast<std::uint8_t>(index % 255));
    }

    disk.openFile(m_fileName, "wb");
    disk.write(dataVector);
    disk.closeFile();

    std::vector<std::uint8_t> offsetVector(dataVector.begin() + 10, dataVector.end());

    disk.openFile(m_fileName, "rb");
    TS_ASSERT_EQUALS(offsetVector, disk.read<std::vector<std::uint8_t>>(10));
    disk.closeFile();
    disk.remove(m_fileName);

    TS_ASSERT_EQUALS(dataVector.size(), disk.operationStats().first  /* write */);
    TS_ASSERT_EQUALS(offsetVector.size(), disk.operationStats().second /* read  */);
}

inline void Test_WDisk::testBlockSize() {
    WDisk disk;
    TS_ASSERT(disk.blockSize() != 0);
    std::stringstream trace("Block size: ",
                    std::ios::app|std::ios::out);
    trace << disk.blockSize();
    TS_TRACE(trace.str().c_str());
}

inline void Test_WDisk::testCreatePath() {
    WDisk disk;

    const std::string relativePathFormA = "./relative/path";
    disk.createPath(relativePathFormA);
    TS_ASSERT(disk.pathExists(relativePathFormA));
    disk.remove(relativePathFormA, true);

    const std::string relativePathFormB = "relative/path";
    disk.createPath(relativePathFormB);
    TS_ASSERT(disk.pathExists(relativePathFormB));
    disk.remove(relativePathFormB, true);

    const std::string absolutePath = "/tmp/absolute";
    disk.createPath(absolutePath);
    TS_ASSERT(disk.pathExists(absolutePath));
    disk.remove(absolutePath);
}

inline void Test_WDisk::testListPath() {
    WDisk disk;

    const std::string dir = "testListPath/";
    disk.createPath(dir);

    const std::string fileOne = "one";
    const std::string fileTwo = "two";
    const std::string fileThr = "three";

    disk.touchFile(dir + fileOne);
    disk.touchFile(dir + fileTwo);
    disk.touchFile(dir + fileThr);

    std::vector<std::string> files = disk.listPathContents(dir);
    for (auto it = files.begin(), end = files.end(); it != end; ++it) {
        TS_TRACE((*it).c_str());
        TS_ASSERT((*it) == fileOne || (*it) == fileTwo || (*it) == fileThr);
    }

}

inline void Test_WDisk::testFailure() {
    WDisk disk;
    try {
        disk.openFile("someFakeFile", "r");
        TS_FAIL("No exception thrown when expected.");
    } catch(std::runtime_error& e) {
        const std::string exceptionErr = e.what();
        TS_TRACE(std::string("Expectation found: ") + e.what());
        TS_ASSERT(exceptionErr.find(WDisk::OPEN_FILE_ERROR)
                != std::string::npos);

    }

    try {
        disk.remove("someFakeFile");
        TS_FAIL("No exception thrown when expected.");
    } catch(std::runtime_error& e) {
        const std::string exceptionErr = e.what();
        TS_TRACE(std::string("Expectation found: ") +
                e.what());
        TS_ASSERT(exceptionErr.find(WDisk::REMOVE_ERROR) !=
                std::string::npos);
    }
}

#endif // TESTING_WRAPPERS_TEST_WDISK_H_
