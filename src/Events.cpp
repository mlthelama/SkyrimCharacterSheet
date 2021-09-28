#include "events.h"
#include "showhandler.h"
#include "scaleform/statsmenu.h"

namespace Events
{
	KeyManager* KeyManager::GetSingleton() {
		static KeyManager singleton;
		return addressof(singleton);
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

			auto key = button->idCode;
			switch (button->device.get()) {
			case DeviceType::kMouse:
				key += kMouseOffset;
				break;
			case DeviceType::kKeyboard:
				key += kKeyboardOffset;
				break;
			case DeviceType::kGamepad:
				key = GetGamepadIndex((RE::BSWin32GamepadDevice::Key)key);
				break;
			default:
				continue;
			}

			auto controlMap = RE::ControlMap::GetSingleton();
			if (ui->GameIsPaused() || !controlMap->IsMovementControlsEnabled()) {
				continue;
			}

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
				break;
			} else if (Scaleform::StatsMenu::IsMenuOpen() && *Settings::closeOnEveryButtonPress) {
				/*should do it*/
				Scaleform::StatsMenu::Close();
				break;
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

	
	uint32_t KeyManager::GetGamepadIndex(RE::BSWin32GamepadDevice::Key a_key) {
		using Key = RE::BSWin32GamepadDevice::Key;

		uint32_t index;
		switch (a_key) {
		case Key::kUp:
			index = 0;
			break;
		case Key::kDown:
			index = 1;
			break;
		case Key::kLeft:
			index = 2;
			break;
		case Key::kRight:
			index = 3;
			break;
		case Key::kStart:
			index = 4;
			break;
		case Key::kBack:
			index = 5;
			break;
		case Key::kLeftThumb:
			index = 6;
			break;
		case Key::kRightThumb:
			index = 7;
			break;
		case Key::kLeftShoulder:
			index = 8;
			break;
		case Key::kRightShoulder:
			index = 9;
			break;
		case Key::kA:
			index = 10;
			break;
		case Key::kB:
			index = 11;
			break;
		case Key::kX:
			index = 12;
			break;
		case Key::kY:
			index = 13;
			break;
		case Key::kLeftTrigger:
			index = 14;
			break;
		case Key::kRightTrigger:
			index = 15;
			break;
		default:
			index = kInvalid;
			break;
		}

		return index != kInvalid ? index + kGamepadOffset : kInvalid;
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