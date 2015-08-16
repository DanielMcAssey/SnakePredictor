// Precompiled Header

// Platform Dependent
// http://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
#ifdef _WIN32
	// -- Windows
	#include <windows.h>
	#include <stdio.h>
	#ifdef _WIN64
	//define something for Windows (64-bit only)
	#endif
#elif __APPLE__
	#include "TargetConditionals.h"
	#if TARGET_OS_MAC
	// Other kinds of Mac OS
	#else
	// Unsupported platform
	#endif
#elif __linux
	// -- Linux
	#include <unistd.h>
	#include <termios.h>
#elif __unix // all unices not caught above
	// -- Unix
#elif __posix
	// -- POSIX
#endif

#include <SDL.h>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

// Fix for TCHAR
#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

#include "Input\InputManager.h"
#include "Screens\ScreenManager.h"