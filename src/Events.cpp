#include "events.h"
#include "showhandler.h"
#include "scaleform/statsmenu.h"

namespace Events
{
	KeyManager* KeyManager::GetSingleton() {
		static KeyManager singleton;
		return std::addressof(singleton);
	}

	auto KeyManager::ProcessEvent(RE::InputEvent* const* p_event, [[maybe_unused]] RE::BSTEventSource<RE::InputEvent*>* p_eventSource)
		-> EventResult
	{
		using EventType = RE::INPUT_EVENT_TYPE;
		using DeviceType = RE::INPUT_DEVICE;

		if (_key == kInvalid) {
			return EventResult::kContinue;
		}

		if (!p_event) {
			return EventResult::kContinue;
		}

		auto ui = RE::UI::GetSingleton();
		auto intfcStr = RE::InterfaceStrings::GetSingleton();
		if (ui->IsMenuOpen(intfcStr->console)) {
			return EventResult::kContinue;
		}

		for (auto event = *p_event; event; event = event->next) {
			if (event->eventType != EventType::kButton) {
				continue;
			}

			auto button = static_cast<RE::ButtonEvent*>(event);
			if (!button->IsDown()) {
				continue;
			}

			//maybefix so mouse btn works as well
			if (!button->IsDown() || button->device != RE::INPUT_DEVICE::kKeyboard) {
				continue;
			}

			auto key = button->idCode;
			//auto device = button->device;
			logger::trace("button code {}"sv, key);

			logger::trace("event input {}, set {}"sv, key, _key);
			if (key == _key) {
				//do shit
				logger::info("configured Key ({}) pressed"sv, key);
				if (Scaleform::StatsMenu::IsMenuOpen()) {
					Scaleform::StatsMenu::Close();
				} else {
					auto showHandler = ShowHandler::GetSingleton();
					showHandler->ShowWindow();
				}
				break;
			} else if (key == RE::BSWin32KeyboardDevice::Key::kEscape && Scaleform::StatsMenu::IsMenuOpen()) {
				Scaleform::StatsMenu::Close();
			} else if (Scaleform::StatsMenu::IsMenuOpen() && *Settings::closeOnEveryButtonPress) {
				/*should do it*/
				Scaleform::StatsMenu::Close();
			}
		}
		return EventResult::kContinue;
	}

	bool KeyManager::Save(const SKSE::SerializationInterface* p_int, uint32_t p_typeCode, uint32_t p_version) {
		Locker lock(_lock);

		if (!p_int->OpenRecord(p_typeCode, p_version)) {
			return false;
		}

		if (!p_int->WriteRecordData(_key)) {
			return false;
		}

		return true;
	}

	bool KeyManager::Load(const SKSE::SerializationInterface* p_int) {
		Locker locker(_lock);

		if (!p_int->ReadRecordData(_key)) {
			return false;
		}

		return true;
	}

	void KeyManager::Clear()
	{
		Locker locker(_lock);
		_key = kInvalid;
	}

	uint32_t KeyManager::GetKey() const
	{
		Locker locker(_lock);
		return _key;
	}

	void KeyManager::SetKey(uint32_t p_key)
	{
		Locker locker(_lock);
		_key = p_key;
	}

	KeyManager::KeyManager() :
		_lock(),
		_key(kInvalid)
	{}

	void SinkEventHandlers()
	{
		auto deviceManager = RE::BSInputDeviceManager::GetSingleton();
		deviceManager->AddEventSink(KeyManager::GetSingleton());
		logger::info("Added Input Event");
	}
}