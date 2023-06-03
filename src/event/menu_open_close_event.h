#pragma once

namespace event {
    class menu_open_close_event final : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
    public:
        using event_result = RE::BSEventNotifyControl;

        static menu_open_close_event* get_singleton();

        static void sink();

        menu_open_close_event(const menu_open_close_event&) = delete;
        menu_open_close_event(menu_open_close_event&&) = delete;
        menu_open_close_event& operator=(const menu_open_close_event&) = delete;
        menu_open_close_event& operator=(menu_open_close_event&&) = delete;

    protected:
        event_result ProcessEvent(const RE::MenuOpenCloseEvent* a_event,
            RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_event_source) override;

    private:
        menu_open_close_event() = default;
        ~menu_open_close_event() override = default;
    };
}
