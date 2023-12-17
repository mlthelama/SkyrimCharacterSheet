#pragma once
#include "util/key_util.h"

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

        uint32_t key_ = util::key_util::k_invalid;
    };
}
