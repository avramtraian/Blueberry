#pragma once

#include "Base.h"
#include "Containers/String.h"

#include <format>

namespace Blueberry {

	class BLUEBERRY_API Logger
	{
	public:
		enum class Verbosity : uint8_t
		{
			None = 0,
			Debug,
			Trace,
			Info,
			Warn,
			Error,
			Fatal
		};

	public:
		static bool Initialize();

		static void Shutdown();

	public:
		static void SetVerbosity(Verbosity verbosity);

		static void Log(Verbosity verbosity, StringView message);

		template<typename... Args>
		static void Log(Verbosity verbosity, StringView message, Args&&... args)
		{
			auto written_ptr = std::vformat_to(m_Buffer, message.CStr(), std::make_wformat_args(Blueberry::Forward<Args>(args)...));
			SizeT written = written_ptr - &m_Buffer[0];
			m_Buffer[written] = 0;

			Log(verbosity, { m_Buffer, written });
		}

	private:
		static CharT m_Buffer[8192];
	};

}

// Engine logs

#if !BLUE_BUILD_SHIPPING
	#define BLUB_CORE_DEBUG(...) ::Blueberry::Logger::Log(::Blueberry::Logger::Verbosity::Debug, __VA_ARGS__)
	#define BLUB_CORE_TRACE(...) ::Blueberry::Logger::Log(::Blueberry::Logger::Verbosity::Trace, __VA_ARGS__)
	#define BLUB_CORE_INFO(...)  ::Blueberry::Logger::Log(::Blueberry::Logger::Verbosity::Info,  __VA_ARGS__)
	#define BLUB_CORE_WARN(...)  ::Blueberry::Logger::Log(::Blueberry::Logger::Verbosity::Warn,  __VA_ARGS__)
	#define BLUB_CORE_ERROR(...) ::Blueberry::Logger::Log(::Blueberry::Logger::Verbosity::Error, __VA_ARGS__)
	#define BLUB_CORE_FATAL(...) ::Blueberry::Logger::Log(::Blueberry::Logger::Verbosity::Fatal, __VA_ARGS__)
#else
	#define BLUB_CORE_DEBUG(...)
	#define BLUB_CORE_TRACE(...)
	#define BLUB_CORE_INFO(...)
	#define BLUB_CORE_WARN(...)
	#define BLUB_CORE_ERROR(...)
	#define BLUB_CORE_FATAL(...)
#endif