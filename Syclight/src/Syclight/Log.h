#pragma once

#ifndef __SYC_LOG_H__
#define __SYC_LOG_H__

#include "Common.h"
#include "Core.h"
#include <memory>
#include <spdlog/spdlog.h>

namespace syc
{
	class SYC_API Log
	{
	public:
		Log() = default;
		~Log() = default;

		static void_ Init();
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() 
		{
			return s_engine_logger;
		};
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_client_logger;
		};

	private:
		static std::shared_ptr<spdlog::logger> s_engine_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};
}

#ifdef _DEBUG
	// 引擎日志打印
	#define SYC_LOG_ENGINE_TRACE(...)   ::syc::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define SYC_LOG_ENGINE_INFO(...)    ::syc::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define SYC_LOG_ENGINE_WARN(...)    ::syc::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define SYC_LOG_ENGINE_ERROR(...)   ::syc::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define SYC_LOG_ENGINE_FATAL(...)   ::syc::Log::GetEngineLogger()->fatal(__VA_ARGS__)

	// 客户端日志打印
	#define SYC_LOG_TRACE(...)          ::syc::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define SYC_LOG_INFO(...)           ::syc::Log::GetClientLogger()->info(__VA_ARGS__)
	#define SYC_LOG_WARN(...)           ::syc::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define SYC_LOG_ERROR(...)          ::syc::Log::GetClientLogger()->error(__VA_ARGS__)
	#define SYC_LOG_FATAL(...)          ::syc::Log::GetClientLogger()->fatal(__VA_ARGS__)
#else
	// 引擎日志打印
	#define SYC_LOG_ENGINE_TRACE(...)
	#define SYC_LOG_ENGINE_INFO(...)
	#define SYC_LOG_ENGINE_WARN(...)
	#define SYC_LOG_ENGINE_ERROR(...)
	#define SYC_LOG_ENGINE_FATAL(...)

	// 客户端日志打印
	#define SYC_LOG_TRACE(...)
	#define SYC_LOG_INFO(...)
	#define SYC_LOG_WARN(...)
	#define SYC_LOG_ERROR(...)
	#define SYC_LOG_FATAL(...)
#endif // DEBUG

#endif // !__SYC_LOG_H__