#include "event/event.h"
#include "mod/mod_manager.h"
#include "scaleform/scaleform.h"
#include "setting/config_setting.h"
#include "setting/game_setting.h"
#include "setting/ini_setting.h"
#include "setting/input_setting.h"

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
            ini_setting::load_settings();
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

void init_mod_support() {
    auto* mod_manager = mod::mod_manager::get_singleton();
    auto* data_handler = RE::TESDataHandler::GetSingleton();

    //check for mods here
    mod_manager->set_armor_rating_rescaled_remake(LoadLibraryW(L"Data/SKSE/Plugins/ArmorRatingRescaledRemake.dll"));
    mod_manager->set_hand_to_hand(LoadLibraryW(L"Data/SKSE/Plugins/HandToHand.dll"));
    mod_manager->set_blade_and_blunt(LoadLibraryW(L"Data/SKSE/Plugins/BladeAndBlunt.dll"));

    mod_manager->set_skyrim_unbound((data_handler && data_handler->LookupModByName("Skyrim Unbound.esp")));
    mod_manager->set_skyrim_souls(LoadLibraryW(L"Data/SKSE/Plugins/SkyrimSoulsRE.dll"));
}

void init_config_setting() {
    auto* config_setting = setting::config_setting::get_singleton();
    try {
        config_setting->load_menu_setting_file();
        config_setting->load_all_faction_setting_files();
        config_setting->load_all_champion_setting_files();
        config_setting->load_all_thane_setting_files();
        config_setting->load_all_player_setting_files();
        config_setting->load_key_setting_file();
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

                init_mod_support();
                init_config_setting();

                scaleform::Register();
                setting::game_setting::get_singleton()->set_settings();

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
    v.HasNoStructUse(true);
    return v;
}();

EXTERN_C [[maybe_unused]] __declspec(dllexport) bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse,
    SKSE::PluginInfo* pluginInfo) {
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
