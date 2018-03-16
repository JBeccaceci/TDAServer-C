/**
*
* @author:      Juan Beccaceci <juanbeccaceci@icloud.com>
* @description: Get platform type (Windows - Linux - MacOS)
* @version:     1.0.0
*
**/
#ifndef PLATFORM_H
#define PLATFORM_H

////////////////////////////////////////////////////////////
/// Platform types
////////////////////////////////////////////////////////////
#define PLATFORM_WINDOWS	0x00
#define PLATFORM_LINUX		0x01
#define PLATFORM_MACOS		0x02

////////////////////////////////////////////////////////////
/// Check Platform
////////////////////////////////////////////////////////////
#if defined(linux) || defined(__linux)
#   define PLATFORM_TYPE PLATFORM_LINUX
#elif defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#   define PLATFORM_TYPE PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#	define PLATFORM_TYPE PLATFORM_MACOS
#else
#	error Platform error
#endif

#endif //<-- PLATFORM_H
