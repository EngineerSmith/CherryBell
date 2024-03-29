#pragma once
#include <memory>
#include <unordered_map>

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
		#define CB_PLATFORM_MACOS
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

#define CB_ENABLE_WARNINGS

#if CB_DEBUG
	#define CB_ENABLE_ASSERTS
	#define CB_PROFILE 1
#endif

#ifdef CB_ENABLE_ASSERTS
	#define CB_CORE_ASSERT(x, ...) {if(!(x)){CB_CORE_ERROR("Assertion Failed: {0} {1} {2}", __LINE__, __FILE__, __VA_ARGS__); __debugbreak();}}
	#define CB_ASSERT(x, ...) {if(!(x)){CB_ERROR("Assertion Failed: {0} {1} {2}", __LINE__, __FILE__, __VA_ARGS__); __debugbreak();}}
	
	#define CB_CORE_NOT_IMPLEMENTED() CB_CORE_ASSERT(false, "Not implemented!")
	#define CB_NOT_IMPLEMENTED() CB_ASSERT(false, "Not implemented!")
#else
	#define CB_CORE_ASSERT(x, ...)
	#define CB_ASSERT(x, ...)
	
	#define CB_CORE_NOT_IMPLEMENTED() __debugbreak()
	#define CB_NOT_IMPLEMENTED() __debugbreak()
#endif // CB_ENABLE_ASSERTS

#ifdef _MSC_VER
#define CB_PRAGMA(arg) __pragma(arg)
#else
#define CB_PRAGMA(arg) _Pragma(arg)
#endif

#define CB_STRING2(x) #x
#define CB_STRING(x) CB_STRING2(x)

#ifdef CB_ENABLE_WARNINGS
	#define CB_COMPILER_WARNING(code, note) CB_PRAGMA(message ( ##__FILE__ "[" CB_STRING(__LINE__) "]: warning CB"#code": "#note ))
#else
	#define CB_COMPILER_WARNING(code, note)
#endif

#define BIT(x) (1 << x)

#define CB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace CherryBell {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args && ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	
	//Hash operator for std::pair in std::unordered_map
	struct pair_hash
	{
		template<class T1, class T2>
		size_t operator() (const std::pair<T1, T2>& pair) const
		{
			return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
		}
	};
	template<class T1, class T2>
	using pair_map = std::unordered_map<T1, T2, pair_hash>;
}
