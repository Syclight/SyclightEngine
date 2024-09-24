#include "sycpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
namespace syc
{
	std::shared_ptr<spdlog::logger> Log::s_engine_logger;
	std::shared_ptr<spdlog::logger> Log::s_client_logger;

	void_ Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_engine_logger = spdlog::stdout_color_mt("Syclight");
		s_engine_logger->set_level(spdlog::level::trace);

		s_client_logger = spdlog::stdout_color_mt("APP");
		s_client_logger->set_level(spdlog::level::trace);

		return void_();
	}
}
