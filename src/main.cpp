#include "events.h"
#include "scaleform/scaleform.h"

void MessageHandler(SKSE::MessagingInterface::Message* a_msg) {
    switch (a_msg->type) {
        case SKSE::MessagingInterface::kDataLoaded:
            logger::info("Data loaded"sv);
            Events::SinkEventHandlers();
            Scaleform::Register();
            break;
    }
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info) {
    try {
        auto path = logger::log_directory();
        if (!path) {
            return false;
        }

        *path /= "ShowStats.log"sv;
        auto sink = make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

        auto log = make_shared<spdlog::logger>("global log"s, move(sink));

        log->set_level(spdlog::level::trace);
        log->flush_on(spdlog::level::trace);


        spdlog::set_default_logger(move(log));
        spdlog::set_pattern("%s(%#): [%^%l%$] %v"s);

        logger::info("ShowStats v{}"sv, Version::NAME);


        a_info->infoVersion = SKSE::PluginInfo::kVersion;
        a_info->name = "ShowStats";
        a_info->version = Version::ASINT;

        if (a_skse->IsEditor()) {
            logger::critical("Loaded in editor, marking as incompatible"sv);
            return false;
        }

        const auto ver = a_skse->RuntimeVersion();
        if (ver < SKSE::RUNTIME_1_5_39) {
            logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
            return false;
        }
    } catch (const std::exception& e) {
        logger::critical("failed, cause {}"sv, e.what());
        return false;
    }

    return true;
}


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
    try {
        logger::info("ShowStats loading"sv);
        try {
            Settings::load();
        } catch (const std::exception& e) { logger::warn("failed to load setting {}"sv, e.what()); }

        SKSE::Init(a_skse);

        switch (*Settings::logLevel) {
            case logTrace:
                spdlog::set_level(spdlog::level::trace);
                spdlog::flush_on(spdlog::level::trace);
                break;
            case logDebug:
                spdlog::set_level(spdlog::level::debug);
                spdlog::flush_on(spdlog::level::debug);
                break;
            case logInfo:
                spdlog::set_level(spdlog::level::info);
                spdlog::flush_on(spdlog::level::info);
                break;
        }

        auto messaging = SKSE::GetMessagingInterface();
        if (!messaging->RegisterListener("SKSE", MessageHandler)) {
            return false;
        }

        auto keyManager = Events::KeyManager::GetSingleton();
        keyManager->SetKey(*Settings::openMenuButton);

        logger::info("ShowStats loaded"sv);
    } catch (const std::exception& e) {
        logger::critical("failed, cause {}"sv, e.what());
        return false;
    }

    return true;
}
