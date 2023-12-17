#pragma once

namespace hook {
    class menu_control_hook : public RE::MenuControls {
    public:
        static void install();

    private:
        RE::BSEventNotifyControl process_event(RE::InputEvent** a_event, RE::BSTEventSource<RE::InputEvent*>* a_source);

        using process_event_type =
            decltype(static_cast<RE::BSEventNotifyControl (RE::MenuControls::*)(RE::InputEvent* const*,
                    RE::BSTEventSource<RE::InputEvent*>*)>(&RE::MenuControls::ProcessEvent));

        static inline REL::Relocation<process_event_type> process_event_;

        static bool is_menu_open(RE::UI*& a_ui);
    };
}  // hook
