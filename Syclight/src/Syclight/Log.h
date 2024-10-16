#pragma once

#ifndef __SYC_LOG_H__
#define __SYC_LOG_H__

#include "Common.h"
#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace syc
{
	class SYC_API Log
	{
	public:
		Log() = default;
		~Log() = default;

		static void_ Init();
		inline static Ref<spdlog::logger>& GetEngineLogger()
		{
			return s_engine_logger;
		};
		inline static Ref<spdlog::logger>& GetClientLogger()
		{
			return s_client_logger;
		};

	private:
		static Ref<spdlog::logger> s_engine_logger;
		static Ref<spdlog::logger> s_client_logger;
	};
}

#ifdef _DEBUG
	//引擎
	#define SYC_CORE_TRACE(...)   ::syc::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define SYC_CORE_INFO(...)    ::syc::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define SYC_CORE_WARN(...)    ::syc::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define SYC_CORE_ERROR(...)   ::syc::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define SYC_CORE_FATAL(...)   ::syc::Log::GetEngineLogger()->critical(__VA_ARGS__)

	//客户端
	#define SYC_TRACE(...)          ::syc::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define SYC_INFO(...)           ::syc::Log::GetClientLogger()->info(__VA_ARGS__)
	#define SYC_WARN(...)           ::syc::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define SYC_ERROR(...)          ::syc::Log::GetClientLogger()->error(__VA_ARGS__)
	#define SYC_FATAL(...)          ::syc::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define SYC_LOG_ENGINE_TRACE(...)
	#define SYC_LOG_ENGINE_INFO(...)
	#define SYC_LOG_ENGINE_WARN(...)
	#define SYC_LOG_ENGINE_ERROR(...)
	#define SYC_LOG_ENGINE_FATAL(...)

	#define SYC_LOG_TRACE(...)
	#define SYC_LOG_INFO(...)
	#define SYC_LOG_WARN(...)
	#define SYC_LOG_ERROR(...)
	#define SYC_LOG_FATAL(...)
#endif // DEBUG

#endif // !__SYC_LOG_H__