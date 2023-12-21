#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

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

#define EXTERN_C extern "C"

#include "Version.h"
