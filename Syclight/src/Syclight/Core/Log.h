#pragma once

#ifndef __SYC_LOG_H__
#define __SYC_LOG_H__

#include "Common.h"
#include "Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// 忽略外部标头中提出的所有警告
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

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
			return s_CoreLogger;
		};
		inline static Ref<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		};

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
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
	#define SYC_CORE_TRACE(...)
	#define SYC_CORE_INFO(...)
	#define SYC_CORE_WARN(...)
	#define SYC_CORE_ERROR(...)
	#define SYC_CORE_FATAL(...)

	#define SYC_TRACE(...)
	#define SYC_INFO(...)
	#define SYC_WARN(...)
	#define SYC_ERROR(...)
	#define SYC_FATAL(...)
#endif // DEBUG

#endif // !__SYC_LOG_H__