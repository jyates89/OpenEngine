/*
 * version.h
 *
 *  Created on: Jun 10, 2017
 *      Author: jyates
 */

#ifndef VERSION_H_
#define VERSION_H_

#include <string>
#include <cstdint>

const std::string VERSION_STR = "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${REL_DESIGNATION}";
const std::uint32_t VERSION_INT = ${VERSION_MAJOR}${VERSION_MINOR}${VERSION_PATCH}UL;

const std::string BUILD_TYPE = "${CMAKE_BUILD_TYPE}";

#endif /* VERSION_H_ */
