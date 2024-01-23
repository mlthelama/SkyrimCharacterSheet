#include "event/event.h"
#include "hook/hook.h"
#include "input/menu_key_input_holder.h"
#include "mod/mod.h"
#include "scaleform/scaleform.h"
#include "setting/input_setting.h"
#include "setting/setting.h"
#include "util/translation.h"

void init_logger() {
    if (static bool initialized = false; !initialized) {
        initialized = true;
    } else {
        return;
    }

    try {
        auto path = logger::log_directory();
        if (!path) {
            stl::report_and_fail("failed to get standard log path"sv);
        }

        *path /= fmt::format("{}.log"sv, Version::PROJECT);
        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
        auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::info);

        spdlog::set_default_logger(std::move(log));
        //spdlog::set_pattern("[%H:%M:%S.%f][%s(%#)][%!][%l] %v"s);
        spdlog::set_pattern("[%H:%M:%S.%f] %s(%#) [%^%l%$] %v"s);

        logger::info("{} v{}"sv, Version::PROJECT, Version::NAME);

        try {
            setting::input_setting::load_setting();
        } catch (const std::exception& e) {
            logger::warn("failed to load ini_setting {}"sv, e.what());
        }

        if (setting::input_setting::get_is_debug()) {
            spdlog::set_level(spdlog::level::trace);
            spdlog::flush_on(spdlog::level::trace);
            setting::input_setting::log();
        }

    } catch (const std::exception& e) {
        logger::critical("failed, cause {}"sv, e.what());
    }
}

void init_config_setting() {
    try {
        setting::setting::load_all_setting();
    } catch (const std::exception& e) {
        logger::warn("failed to load json setting {}"sv, e.what());
    }
}

EXTERN_C [[maybe_unused]] __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
    init_logger();

    logger::info("{} loading"sv, Version::PROJECT);
    logger::info("Game version {}"sv, a_skse->RuntimeVersion().string());

    Init(a_skse);

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* a_msg) {
        switch (a_msg->type) {
            case SKSE::MessagingInterface::kDataLoaded:
                logger::info("Begin Data loaded"sv);
                event::sink_event_handlers();

                init_config_setting();
                mod::mod::init_mod_support();

                util::translation::get_singleton()->build_translation_map();

                scaleform::Register();
                input::menu_key_input_holder::get_singleton()->set_all();

                hook::hook::install();

                logger::info("Done with Data loaded"sv);
                break;
        }
    });

    logger::info("{} loaded"sv, Version::PROJECT);
    return true;
}

EXTERN_C [[maybe_unused]] __declspec(dllexport) constinit auto SKSEPlugin_Version = []() noexcept {
    SKSE::PluginVersionData v;
    v.PluginName(Version::PROJECT);
    v.AuthorName(Version::AUTHOR);
    v.PluginVersion({ Version::MAJOR, Version::MINOR, Version::PATCH, Version::BETA });
    v.UsesAddressLibrary(true);
    v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST });
    //v.HasNoStructUse(true);
    v.UsesNoStructs();
    return v;
}();

EXTERN_C [[maybe_unused]] __declspec(dllexport) bool SKSEAPI
    SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* pluginInfo) {
    pluginInfo->name = SKSEPlugin_Version.pluginName;
    pluginInfo->infoVersion = SKSE::PluginInfo::kVersion;
    pluginInfo->version = SKSEPlugin_Version.pluginVersion;

    if (a_skse->IsEditor()) {
        logger::critical("Loaded in editor, marking as incompatible"sv);
        return false;
    }

    const auto ver = a_skse->RuntimeVersion();
    if (ver < SKSE::RUNTIME_SSE_1_5_39) {
        logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
        return false;
    }

    return true;
}
