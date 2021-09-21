#pragma once

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include <fmt/format.h>

#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif

//typedef std::unordered_map<std::string, std::string> ValueMap;
//typedef std::unordered_map<std::string, RE::ActorValue> ActorMap;
//typedef std::map<std::string, std::string> ValueMap;
//typedef std::map<std::string, RE::ActorValue> ActorMap;


using namespace std::literals;

namespace stl
{
	//using namespace SKSE::stl;
	using namespace SKSE::util;

	constexpr std::string_view safe_string(const char* a_str) { return a_str ? a_str : ""sv; }
}

namespace logger = SKSE::log;

#define DLLEXPORT __declspec(dllexport)
