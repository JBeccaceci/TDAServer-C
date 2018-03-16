/**
*
* @author:      Juan Beccaceci <juanbeccaceci@icloud.com>
* @description: Get platform type (Windows - Linux - MacOS)
* @version:     1.0.0
*
**/
#ifndef PLATAFORM_H
#define PLATAFORM_H

////////////////////////////////////////////////////////////
/// Plataform types
////////////////////////////////////////////////////////////
#define PLATFORM_WINDOWS	0x00
#define PLATFORM_LINUX		0x01
#define PLATFORM_MACOS		0x02

////////////////////////////////////////////////////////////
/// Check plataform
////////////////////////////////////////////////////////////
#if defined(linux) || defined(__linux)
#   define PLATFORM_TYPE PLATFORM_LINUX
#elif defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#   define PLATFORM_TYPE PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#	define PLATFORM_TYPE PLATFORM_MACOS
#else
#	error Plataform error
#endif

#endif //<-- PLATAFORM_H