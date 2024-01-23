#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

#include <spdlog/sinks/basic_file_sink.h>

#include "magic_enum.hpp"
#include "nlohmann/json.hpp"
#include <ankerl/unordered_dense.h>
#include <ClibUtil/string.hpp>
#include <codecvt>

using namespace std::literals;

struct string_hash
{
    using is_transparent = void;  // enable heterogeneous overloads
    using is_avalanching = void;  // mark class as high quality avalanching hash
                                  
    [[nodiscard]] std::uint64_t operator()(std::string_view str) const noexcept
    {
        return ankerl::unordered_dense::hash<std::string_view>{}(str);
    }
};

template <class D>
using string_map = ankerl::unordered_dense::segmented_map<std::string, D, string_hash, std::equal_to<>>;

namespace stl {
    using namespace SKSE::stl;
}

namespace logger = SKSE::log;

#define EXTERN_C extern "C"

#include "Version.h"
