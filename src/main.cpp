#include "events.h"
#include "scaleform/scaleform.h"

void InitLogger() {
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
    } else {
        return;
    }

    try {
#ifndef NDEBUG
        auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
        auto path = logger::log_directory();
        if (!path) {
            stl::report_and_fail("failed to get standard log path"sv);
        }

        *path /= Version::PROJECT;
        *path += ".log"sv;
        auto sink = make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif
        auto log = make_shared<spdlog::logger>("global log"s, move(sink));

#ifndef NDEBUG
        log->set_level(spdlog::level::trace);
#else
        log->set_level(spdlog::level::trace);
        log->flush_on(spdlog::level::trace);
#endif

        spdlog::set_default_logger(move(log));
        spdlog::set_pattern("[%H:%M:%S.%f] %s(%#) [%^%l%$] %v"s);

        logger::info("{} v{}"sv, Version::PROJECT, Version::NAME);

        try {
            Settings::load();
            logger::info("Settings Loaded"sv);
        } catch (const std::exception& e) { logger::warn("failed to load setting {}"sv, e.what()); }

        switch (*Settings::logLevel) {
            case _constLogTrace:
                spdlog::set_level(spdlog::level::trace);
                spdlog::flush_on(spdlog::level::trace);
                break;
            case _constLogDebug:
                spdlog::set_level(spdlog::level::debug);
                spdlog::flush_on(spdlog::level::debug);
                break;
            case _constLogInfo:
                spdlog::set_level(spdlog::level::info);
                spdlog::flush_on(spdlog::level::info);
                break;
        }
    } catch (const std::exception& e) { logger::critical("failed, cause {}"sv, e.what()); }
}

extern "C" DLLEXPORT constexpr auto SKSEPlugin_Version = []() {
    SKSE::PluginVersionData v{};
    v.PluginVersion(Version::ASINT);
    v.PluginName(Version::PROJECT.data());
    v.AuthorName(Version::AUTHOR);
    v.UsesAddressLibrary(true);
    return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
    try {
        InitLogger();

        logger::info("ShowStats loading"sv);

        SKSE::Init(a_skse);

        SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* a_msg) {
            switch (a_msg->type) {
                case SKSE::MessagingInterface::kDataLoaded:
                    logger::info("Data loaded"sv);
                    Events::SinkEventHandlers();
                    Scaleform::Register();
                    break;
            }
        });

        logger::info("ShowStats loaded"sv);
    } catch (const std::exception& e) {
        logger::critical("failed, cause {}"sv, e.what());
        return false;
    }

    return true;
}
