/*
 * WDisk.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: jyates
 */

#include "WDisk.h"

extern "C" {
#include <dirent.h>
}

#include <algorithm>
#include <utility>

void WDisk::createPath(const std::string& path) const {
    size_t lastPos = 0;
    if (path.length() > 1 && path[0] == '/') {
        lastPos = 1;
    } else if (path.length() > 2 &&
            path[0] == '.' && path[1] == '/') {
        lastPos = 2;
    }
    size_t currentPos = 0;
    while ((currentPos = path.find_first_of('/', lastPos)) != std::string::npos) {
        std::string currentPath = path.substr(0,
                path.size() - (path.size() - currentPos));
        lastPos = currentPos + 1;
        if (!pathExists(currentPath) &&
                mkdir(currentPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
                != 0) {
            throw std::runtime_error(MK_DIR_ERROR + std::strerror(errno));
        }
    }
    if (currentPos != (path.size() - 1)) {
        if (!pathExists(path) &&
                mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
            throw std::runtime_error(MK_DIR_ERROR + std::strerror(errno));
        }
    }
}

std::vector<std::string> WDisk::listPathContents(
        const std::string& path) const {
    if (!S_ISDIR(fileStat(path).st_mode)) {
        throw std::invalid_argument(NOT_A_DIR_ERROR);
    }
    DIR* dirHandle = opendir(path.c_str());
    if (dirHandle == nullptr) {
        throw std::runtime_error(OPEN_DIR_ERROR + std::strerror(errno));
    }
    std::vector<std::string> fileList;
    struct dirent* next = nullptr;
    while ((next = readdir(dirHandle)) != nullptr) {
        if (std::strcmp(next->d_name, ".") &&
                std::strcmp(next->d_name, "..")) {
            fileList.push_back(next->d_name);
        }
    }
    closedir(dirHandle);
    return fileList;
}

const std::string WDisk::REMOVE_ERROR     = "failed to remove file: ";
const std::string WDisk::BLOCK_ERROR      = "failed to get disk block size: ";
const std::string WDisk::FLUSH_ERROR      = "failed to flush buffer: ";
const std::string WDisk::SEEK_ERROR       = "failed to seek position: ";
const std::string WDisk::NOT_OPEN_ERROR   = "no file is currently open";
const std::string WDisk::STR_READ_ERROR   = "failed to read string data: ";
const std::string WDisk::BIN_READ_ERROR   = "failed to read binary data: ";
const std::string WDisk::STR_WRITE_ERROR  = "failed to write string data: ";
const std::string WDisk::BIN_WRITE_ERROR  = "failed to write binary data: ";
const std::string WDisk::STAT_ERROR       = "failed to stat file: ";
const std::string WDisk::FSTAT_ERROR      = "failed to fstat file: ";
const std::string WDisk::MK_DIR_ERROR     = "failed to create directory: ";
const std::string WDisk::NOT_A_DIR_ERROR  = "path does not lead to a directory: ";
const std::string WDisk::OPEN_DIR_ERROR   = "failed to open directory for reading: ";
const std::string WDisk::OPEN_FILE_ERROR  = "failed to open file: ";
const std::string WDisk::FILE_CLOSE_ERROR = "failed to close file: ";
const std::string WDisk::TIMESTAMP_ERROR  = "failed to update file timestamp: ";
const std::string WDisk::TOUCH_ERROR      = "failed to touch file: ";
