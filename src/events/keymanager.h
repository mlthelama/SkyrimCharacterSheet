#pragma once
#include "handler/showhandler.h"
#include "scaleform/factionmenu.h"
#include "scaleform/statsmenu.h"

class KeyManager : public RE::BSTEventSink<RE::InputEvent*> {
public:
    using EventResult = RE::BSEventNotifyControl;
    using ShowMenu = MenuUtil::ShowMenu;

    static KeyManager* GetSingleton() {
        static KeyManager singleton;
        return std::addressof(singleton);
    }

    auto ProcessEvent(RE::InputEvent* const* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::InputEvent*>* a_eventSource) -> EventResult {
        using EventType = RE::INPUT_EVENT_TYPE;
        using DeviceType = RE::INPUT_DEVICE;

        if (_key == kInvalid) {
            return EventResult::kContinue;
        }

        if (!a_event) {
            return EventResult::kContinue;
        }

        auto ui = RE::UI::GetSingleton();
        auto intfcStr = RE::InterfaceStrings::GetSingleton();
        if (ui->IsMenuOpen(intfcStr->console)) {
            return EventResult::kContinue;
        }

        for (auto event = *a_event; event; event = event->next) {
            if (event->eventType != EventType::kButton) {
                continue;
            }

            auto button = static_cast<RE::ButtonEvent*>(event);
            if (!button->IsDown()) {
                continue;
            }

            auto controlMap = RE::ControlMap::GetSingleton();
            if (!controlMap->IsMovementControlsEnabled()) {
                continue;
            }

            /*if the game is not paused with the menu, it triggers the menu always in the background*/
            auto showHandler = ShowHandler::GetSingleton();
            if (ui->GameIsPaused() && !showHandler->IsMenuOpen()) {
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

            if (key == _key) {
                logger::debug("configured Key ({}) pressed"sv, key);
                showHandler->HandleMainButtonPress();
                break;
            } else if (key == RE::BSWin32KeyboardDevice::Key::kEscape) {
                showHandler->CloseAllWindows();
                break;
            } else if (key == *Settings::openFactionMenuButton) {
                showHandler->HandleNextMenuButtonPress();
            }
        }
        return EventResult::kContinue;
    }

    void SetKey(uint64_t a_key) { _key = a_key; }

    static void Sink() {
        auto deviceManager = RE::BSInputDeviceManager::GetSingleton();
        deviceManager->AddEventSink(KeyManager::GetSingleton());
    }

    KeyManager() = default;
    KeyManager(const KeyManager&) = delete;
    KeyManager(KeyManager&&) = delete;
    virtual ~KeyManager() = default;

    KeyManager& operator=(const KeyManager&) = delete;
    KeyManager& operator=(KeyManager&&) = delete;
private:
    uint32_t GetGamepadIndex(RE::BSWin32GamepadDevice::Key a_key) {
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

    enum : uint32_t {
        kInvalid = static_cast<uint32_t>(-1),
        kKeyboardOffset = 0,
        kMouseOffset = 256,
        kGamepadOffset = 266
    };

    uint64_t _key = kInvalid;
};
