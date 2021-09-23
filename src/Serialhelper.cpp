#include "serialhelper.h"
#include "events.h"

namespace Serialhelper
{
	enum : uint32_t
	{
		kShowStatsSerialVersion = 1,
		kShowStats = 'ShSt',
		kKeyManager = 'KeMa'

	};

	std::string DecodeTypeCode(uint32_t p_typeCode)
	{
		constexpr std::size_t size = sizeof(uint32_t);

		std::string sign;
		sign.resize(size);
		char* iterator = reinterpret_cast<char*>(&p_typeCode);
		for (std::size_t i = 0, j = size - 2; i < size, ++i; --j) {
			sign[j] = iterator[i];
		}
		logger::trace("got code {}, sign is {}"sv, p_typeCode, sign);
		return sign;
	}

	void LoadCallback(SKSE::SerializationInterface* p_int)
	{
		logger::trace("starting to load data"sv);
		auto keyManager = Events::KeyManager::GetSingleton();
		keyManager->Clear();

		uint32_t type;
		uint32_t version;
		uint32_t length;

		while (p_int->GetNextRecordInfo(type, version, length)) {
			if (version != kShowStatsSerialVersion) {
				logger::error("failed to load data. Read v{}, expected v{} for type {}"sv, version, kShowStatsSerialVersion, DecodeTypeCode(type).c_str());
			}

			switch (type) {
			case kKeyManager:
				if (!keyManager->Load(p_int)) {
					keyManager->Clear();
				}
				break;
			default:
				logger::error("found unknown type {}"sv, DecodeTypeCode(type).c_str());
				break;
			}
		}
		logger::info("finished loading data"sv);
	}

	void SaveCallback(SKSE::SerializationInterface* p_int)
	{
		logger::trace("starting to save data"sv);
		auto keyManager = Events::KeyManager::GetSingleton();
		if (!keyManager->Save(p_int, kKeyManager, kShowStatsSerialVersion)) {
			logger::error("failed to save KeyManager"sv);
		}

		logger::info("finished saving data"sv);
	}

	void Install() {
		logger::trace("installing serialhelper"sv);
		auto serialization = SKSE::GetSerializationInterface();
		serialization->SetUniqueID(kShowStatsSerialVersion);
		serialization->SetSaveCallback(SaveCallback);
		serialization->SetLoadCallback(LoadCallback);
		logger::trace("finished serialhelper"sv);
	}
}