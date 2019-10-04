#pragma once
#include "core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace CherryBell {
	class CB_API Log {
	public:
		static void Init();
		inline static std::shared_ptr < spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr < spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr <spdlog::logger> s_coreLogger;
		static std::shared_ptr < spdlog::logger> s_clientLogger;
	};
}

#if defined(CB_DEBUG) || defined(CB_RELEASE)
	// Core log macros
	#define CB_CORE_FATAL(...)	::CherryBell::Log::GetCoreLogger()->fatal(__VA_ARGS__)
	#define CB_CORE_ERROR(...)	::CherryBell::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define CB_CORE_WARN(...)	::CherryBell::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define CB_CORE_INFO(...)	::CherryBell::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define CB_CORE_TRACE(...)	::CherryBell::Log::GetCoreLogger()->trace(__VA_ARGS__)
	
	// Client log macros
	#define CB_FATAL(...)		::CherryBell::Log::GetClientLogger()->fatal(__VA_ARGS__)
	#define CB_ERROR(...)		::CherryBell::Log::GetClientLogger()->error(__VA_ARGS__)
	#define CB_WARN(...)		::CherryBell::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define CB_INFO(...)		::CherryBell::Log::GetClientLogger()->info(__VA_ARGS__)
	#define CB_TRACE(...)		::CherryBell::Log::GetClientLogger()->trace(__VA_ARGS__)
#else //strip from Dist builds
	#define CB_CORE_FATAL(...)
	#define CB_CORE_ERROR(...)
	#define CB_CORE_WARN(...)
	#define CB_CORE_INFO(...)
	#define CB_CORE_TRACE(...)
	#define CB_FATAL(...)
	#define CB_ERROR(...)
	#define CB_WARN(...)
	#define CB_INFO(...)
	#define CB_TRACE(...)
#endif