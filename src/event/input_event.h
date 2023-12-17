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

        std::set<uint32_t> open_key_combo_;
        std::set<uint32_t> close_key_combo_;
        std::set<uint32_t> open_inventory_key_combo_;
        std::set<uint32_t> close_inventory_key_combo_;

        std::set<uint32_t> key_down_list_;

        static void add_key_down(std::set<uint32_t>& a_set, uint32_t key);

        static void remove_key_down(std::set<uint32_t>& a_set, uint32_t key);

        bool is_one_combo_empty();

        static void log_combo_set(std::set<uint32_t>& a_needed, std::set<uint32_t>& a_down);
    };
}
