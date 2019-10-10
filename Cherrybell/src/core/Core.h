#pragma once
#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
	/* Windows x64  */
		#define CB_PLATFORM_WINDOWS
	#else
	/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define CB_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define HZ_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define CB_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define CB_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef CB_ENABLE_ASSERTS
	#define CB_CORE_ASSERT(x, ...) {if(!(x)){CB_CORE_ERROR("Assertion Failed: {0} {1} {2}", __LINE__, __FILE__, __VA_ARGS__); __debugbreak();}}
	#define CB_ASSERT(x, ...) {if(!(x)){CB_ERROR("Assertion Failed: {0} {1} {2}", __LINE__, __FILE__, __VA_ARGS__); __debugbreak();}}
#else
	#define CB_CORE_ASSERT(x, ...)
	#define CB_ASSERT(x, ...)
#endif // CB_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define CB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace CherryBell {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}