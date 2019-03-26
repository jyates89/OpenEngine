/*
 * WDisk.h
 *
 *  Created on: Jun 24, 2017
 *      Author: jyates
 */

#ifndef WRAPPERS_WDISK_H_
#define WRAPPERS_WDISK_H_

#include "Types/StandardDefines.h"

#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <stdexcept>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cerrno>

extern "C" {
#include <sys/stat.h>
#include <fcntl.h>
}

class WDisk {
    friend class Test_WDisk;
public:
    WDisk();
    WDisk(WDisk& wdisk);

    WDisk& operator=(const WDisk& right);

    ~WDisk();

    void openFile(const std::string& fileName, const std::string& fileMode);
    void closeFile();

    void touchFile(const std::string& fileName) const;

    void remove(const std::string& fileName, bool recursive = false) const;

    bool pathExists(const std::string& path) const;

    std::size_t size(const std::string& path = "") const;
    std::size_t blockSize() const;

    void createPath(const std::string& path) const;

    std::vector<std::string> listPathContents(const std::string& path) const;

    std::chrono::seconds lastModified(const std::string& path = "") const;

    void flushBuffer();

    void seekPosition(std::size_t position);
    void checkFileHandle() const;

    void write(const std::string& line, std::size_t position = 0,
            bool validate = true);
    void write(const std::vector<std::string>& lines, std::size_t position = 0);
    void write(const std::vector<std::uint8_t>& data, std::size_t position = 0);

    template<typename Readable>
    Readable read(std::size_t position = 0, bool validate = true);

    std::pair<std::size_t, std::size_t> operationStats() const;

private:
    std::string m_fileName;

    std::size_t m_readBytes;
    std::size_t m_writeBytes;

    std::size_t m_blockSize;

    FILE* m_fileHandle;

    // Various thrown error messages will be declared here
    //  to reduce change count, in case they need to be changed
    //  later on.
    static const std::string REMOVE_ERROR;
    static const std::string BLOCK_ERROR;
    static const std::string FLUSH_ERROR;
    static const std::string SEEK_ERROR;
    static const std::string NOT_OPEN_ERROR;
    static const std::string STR_READ_ERROR;
    static const std::string BIN_READ_ERROR;
    static const std::string STR_WRITE_ERROR;
    static const std::string BIN_WRITE_ERROR;
    static const std::string STAT_ERROR;
    static const std::string FSTAT_ERROR;
    static const std::string MK_DIR_ERROR;
    static const std::string NOT_A_DIR_ERROR;
    static const std::string OPEN_DIR_ERROR;
    static const std::string OPEN_FILE_ERROR;
    static const std::string FILE_CLOSE_ERROR;
    static const std::string TIMESTAMP_ERROR;
    static const std::string TOUCH_ERROR;

    struct stat fileStat(const std::string& path = "") const;
};

inline WDisk::WDisk() :
        m_readBytes(0), m_writeBytes(0), m_blockSize(0), m_fileHandle(nullptr) {

    m_blockSize = blockSize();
}

inline WDisk::WDisk(WDisk& wdisk) :
        m_fileName(wdisk.m_fileName), m_readBytes(wdisk.m_readBytes), m_writeBytes(
                wdisk.m_writeBytes), m_blockSize(wdisk.m_blockSize), m_fileHandle(
                wdisk.m_fileHandle) {
}

inline WDisk& WDisk::operator=(const WDisk& right) {
    if (this != &right) {
        m_fileName = right.m_fileName;
        m_readBytes = right.m_readBytes;
        m_writeBytes = right.m_writeBytes;
        m_blockSize = right.m_blockSize;
        m_fileHandle = right.m_fileHandle;
    }
    return *this;
}

inline WDisk::~WDisk() {
    if (m_fileHandle != nullptr) {
        closeFile();
    }
}

inline void WDisk::openFile(const std::string& fileName,
        const std::string& fileMode) {
    if (m_fileHandle != nullptr) {
        closeFile();
    }
    if ((m_fileHandle = std::fopen(fileName.c_str(), fileMode.c_str()))
            == nullptr) {
        throw std::runtime_error(OPEN_FILE_ERROR + std::strerror(errno));
    }
    m_fileName = fileName;
}

inline void WDisk::closeFile() {
    if (std::fclose(m_fileHandle) != 0) {
        throw std::runtime_error(FILE_CLOSE_ERROR + std::strerror(errno));
    }
    m_fileHandle = nullptr;
}

inline void WDisk::touchFile(const std::string& fileName) const {
    int fileDescriptor = open(fileName.c_str(),
    O_WRONLY | O_CREAT | O_NOCTTY | O_NONBLOCK, 0664);
    if (fileDescriptor < 0) {
        throw std::runtime_error(TOUCH_ERROR + std::strerror(errno));
    }
    if (futimens(fileDescriptor, nullptr) != 0) {
        throw std::runtime_error(TIMESTAMP_ERROR + std::strerror(errno));
    }
    if (close(fileDescriptor) != 0) {
        throw std::runtime_error(FILE_CLOSE_ERROR + std::strerror(errno));
    }
}

inline void WDisk::remove(const std::string& fileName, bool recursive) const {
    if (fileName == "." || fileName == ".." || fileName == "/") {
        return;
    }
    if (std::remove(fileName.c_str()) != 0) {
        throw std::runtime_error(REMOVE_ERROR + std::strerror(errno));
    }
    if (recursive) {
        std::size_t fSlash = fileName.find_last_of('/');
        if (fSlash != std::string::npos) {
            std::string next = fileName.substr(0, fSlash);
            remove(next, recursive);
        }
    }
}

inline bool WDisk::pathExists(const std::string& path) const {
    struct stat thisStat;
    if (stat(path.c_str(), &thisStat) != 0) {
        return false;
    }
    return true;
}

inline size_t WDisk::size(const std::string& path) const {
    return fileStat(path).st_size;
}

inline size_t WDisk::blockSize() const {
    struct stat thisStat;
    if (stat(".", &thisStat) != 0) {
        throw std::runtime_error(BLOCK_ERROR + std::strerror(errno));
    }
    return thisStat.st_blksize;
}

inline std::chrono::seconds WDisk::lastModified(const std::string& path) const {
    return std::chrono::seconds(fileStat(path).st_mtim.tv_sec);
}

inline void WDisk::flushBuffer() {
    if (std::fflush(m_fileHandle) != 0) {
        throw std::runtime_error(FLUSH_ERROR + std::strerror(errno));
    }
}

inline void WDisk::seekPosition(std::size_t position) {
    if (std::fseek(m_fileHandle, position, SEEK_SET) != 0) {
        throw std::runtime_error(SEEK_ERROR + std::strerror(errno));
    }
}

inline void WDisk::checkFileHandle() const {
    if (m_fileHandle == nullptr) {
        throw std::runtime_error(NOT_OPEN_ERROR);
    }
}

template<>
inline std::string WDisk::read<std::string>(std::size_t position,
        bool validate) {
    if (validate) {
        checkFileHandle();
        if (position > 0) {
            seekPosition(position);
        }
    }
    std::vector<char> buffer(m_blockSize);
    if (std::fgets(buffer.data(), m_blockSize, m_fileHandle) != buffer.data()) {
        if (std::feof(m_fileHandle) == 0) {
            throw std::runtime_error(STR_READ_ERROR + std::strerror(errno));
        }
    }
    std::string line(buffer.data());
    m_readBytes += line.length();
    return line;
}

template<>
inline std::vector<std::string> WDisk::read<std::vector<std::string>>(
        std::size_t position, bool validate) {
    checkFileHandle();
    if (position > 0) {
        seekPosition(position);
    }
    std::string line = read<std::string>(position);
    std::vector<std::string> buffer;
    while (line.length() > 0) {
        buffer.push_back(line);
        line = read<std::string>(position, false);
    }
    return buffer;
}

template<>
inline std::vector<std::uint8_t> WDisk::read<std::vector<std::uint8_t>>(
        std::size_t position, bool validate) {
    checkFileHandle();
    if (position > 0) {
        seekPosition(position);
    }
    struct stat thisStat = fileStat();
    std::size_t allocationSize = m_blockSize;
    if (static_cast<std::size_t>(thisStat.st_size) < m_blockSize) {
        allocationSize = thisStat.st_size;
    }
    std::vector<std::uint8_t> buffer(allocationSize);
    std::size_t bytesRead = std::fread(buffer.data(), 1, allocationSize,
            m_fileHandle);
    if (bytesRead != allocationSize && std::feof(m_fileHandle) == 0) {
        throw std::runtime_error(BIN_READ_ERROR + std::strerror(errno));
    }
    m_readBytes += bytesRead;
    if (bytesRead < allocationSize) {
        buffer.resize(bytesRead);
    }
    return buffer;
}

inline void WDisk::write(const std::vector<std::uint8_t>& data,
        std::size_t position) {
    checkFileHandle();
    if (position > 0) {
        seekPosition(position);
    }
    std::size_t totalBytesWritten = 0;
    while (totalBytesWritten < data.size()) {
        totalBytesWritten += std::fwrite(data.data() + totalBytesWritten, 1,
                data.size() - totalBytesWritten > m_blockSize ?
                        m_blockSize : data.size() % m_blockSize, m_fileHandle);
    }
    if (totalBytesWritten != data.size()) {
        throw std::runtime_error(BIN_WRITE_ERROR + std::strerror(errno));
    }
    m_writeBytes += totalBytesWritten;
}

inline void WDisk::write(const std::vector<std::string>& lines,
        std::size_t position) {
    checkFileHandle();
    if (position > 0) {
        seekPosition(position);
    }
    for (auto it = lines.begin(), end = lines.end(); it != end; ++it) {
        write(*it, position, false);
    }
}

inline void WDisk::write(const std::string& line, std::size_t position,
        bool validate) {
    if (validate) {
        checkFileHandle();
        if (position > 0) {
            seekPosition(position);
        }
    }
    if (std::fputs(line.c_str(), m_fileHandle) < 0) {
        throw std::runtime_error(STR_WRITE_ERROR + std::strerror(errno));
    }
    m_writeBytes += line.length();
}

inline std::pair<std::size_t, std::size_t> WDisk::operationStats() const {
    return {m_writeBytes, m_readBytes};
}

inline struct stat WDisk::fileStat(const std::string& path) const {
    struct stat thisStat;
    if (path.length() > 0) {
        if (stat(path.c_str(), &thisStat) != 0) {
            throw std::runtime_error(STAT_ERROR + std::strerror(errno));
        }
    } else {
        if (fstat(fileno(m_fileHandle), &thisStat) != 0) {
            throw std::runtime_error(FSTAT_ERROR + std::strerror(errno));
        }
    }
    return thisStat;
}

#endif /* WRAPPERS_WDISK_H_ */
