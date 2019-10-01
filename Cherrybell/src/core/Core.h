#pragma once

#ifdef CB_PLATFORM_WINDOWS
	#ifdef CB_BUILD_DLL
		#define CB_API __declspec(dllexport)
	#else
		#define CB_API __declspec(dllimport)
	#endif // CB_BUILD_DLL
#else
	#error CherryBell only supports Windows
#endif // CB_PLATFORM_WINDOWS


