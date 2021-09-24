#include "papyrus.h"
#include "events.h"
#include "serialhelper.h"
#include "hooks.h"
#include "scaleform/scaleform.h"
#include "constants.h"

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		logger::info("Data loaded"sv);
		Events::SinkEventHandlers();
		Scaleform::Register();
		break;
	}
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		return false;
	}

	*path /= "ShowStats.log"sv;
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	//log->set_level(spdlog::level::info);
	//log->flush_on(spdlog::level::warn);

	log->set_level(spdlog::level::trace);
	log->flush_on(spdlog::level::trace);
#endif


	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

	logger::info("ShowStats v{}"sv, version_string);
	

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = "ShowStats";
	a_info->version = version_major;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}

	return true;
}


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	logger::info("ShowStats loaded"sv);
	try {
		Settings::load();
	} catch (const std::exception& e) {
		logger::warn("failed to load setting {}"sv, e.what());
	}
	
	SKSE::Init(a_skse);


	switch (*Settings::logLevel) {
	case constants::logTrace:
		spdlog::set_level(spdlog::level::trace);
		spdlog::flush_on(spdlog::level::trace);
		break;
	case constants::logDebug:
		spdlog::set_level(spdlog::level::debug);
		spdlog::flush_on(spdlog::level::debug);
		break;
	case constants::logInfo:
		spdlog::set_level(spdlog::level::info);
		spdlog::flush_on(spdlog::level::info);
		break;
	}

	auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}
	//not needed for now
	//hooks::install();

	Papyrus::Register();

	Serialhelper::Install();

	return true;
}
