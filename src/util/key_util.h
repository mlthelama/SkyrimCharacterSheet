#pragma once

namespace util {
    class key_util {
    public:
        enum : uint32_t {
            k_invalid = static_cast<uint32_t>(-1),
            k_keyboard_offset = 0,
            k_mouse_offset = 256,
            k_gamepad_offset = 266
        };

        static void get_key_id(RE::INPUT_DEVICE a_device, uint32_t& a_key);

    private:
        static uint32_t get_gamepad_index(RE::BSWin32GamepadDevice::Key a_key);
    };
}  // util
