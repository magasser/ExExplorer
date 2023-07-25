#include "eepch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init()
{
	spdlog::set_pattern("[%T] %^[%l]%$: %v");

	auto duplicateFilter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(10));

	duplicateFilter->add_sink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	duplicateFilter->add_sink(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/ExExplorer.log", true));

	s_Logger = std::make_shared<spdlog::logger>("ExExplorer", duplicateFilter);
	s_Logger->set_level(spdlog::level::trace);

#if defined(EE_DEBUG)
	s_Logger->flush_on(spdlog::level::trace);
#elif defined(EE_RELEASE)
	s_Logger->flush_on(spdlog::level::info);
#endif
}
