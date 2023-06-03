#pragma once

namespace event {
    class input_event final : public RE::BSTEventSink<RE::InputEvent*> {
    public:
        using event_result = RE::BSEventNotifyControl;

        static input_event* get_singleton();

        static void sink();

        input_event(const input_event&) = delete;
        input_event(input_event&&) = delete;
        input_event& operator=(const input_event&) = delete;
        input_event& operator=(input_event&&) = delete;

    protected:
        event_result ProcessEvent(RE::InputEvent* const* a_event,
            RE::BSTEventSource<RE::InputEvent*>* a_event_source) override;

    private:
        input_event() = default;
        ~input_event() override = default;

        static uint32_t get_gamepad_index(RE::BSWin32GamepadDevice::Key a_key);

        enum : uint32_t {
            k_invalid = static_cast<uint32_t>(-1),
            k_keyboard_offset = 0,
            k_mouse_offset = 256,
            k_gamepad_offset = 266
        };

        uint32_t key_ = k_invalid;
    };
}
