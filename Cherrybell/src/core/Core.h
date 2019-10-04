#pragma once

#ifdef CB_PLATFORM_WINDOWS
	#ifdef CB_BUILD_DLL
		#define CB_API __declspec(dllexport)
		//#define IMGUI_API __declspec(dllexport)
	#else
		#define CB_API __declspec(dllimport)
		//#define IMGUI_API __declspec(dllimport)
	#endif // CB_BUILD_DLL
#else
	#error CherryBell does not support this platform
#endif // CB_PLATFORM_WINDOWS

#ifdef CB_ENABLE_ASSERTS
	#define CB_CORE_ASSERT(x, ...) {if(!x){CB_CORE_ERROR("Assertion Failed: {0} {1} {2}", __LINE__, __FILE__, __VA_ARGS__); __debugbreak();}}
	#define CB_ASSERT(x, ...) {if(!x){CB_ERROR("Assertion Failed: {0} {1} {2}", __LINE__, __FILE__, __VA_ARGS__); __debugbreak();}}
#else
	#define CB_CORE_ASSERT(x, ...)
	#define CB_ASSERT(x, ...)
#endif // CB_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define CB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
