#pragma once

#define WIN32_LEAN_AND_MEAN

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

#include <spdlog/sinks/basic_file_sink.h>

#include "magic_enum.hpp"
#include "nlohmann/json.hpp"

using namespace std::literals;

namespace stl {
    using namespace SKSE::stl;
}

namespace logger = SKSE::log;

#include "Version.h"
#include "setting/ini_setting.h"
#include "util/utils.h"
