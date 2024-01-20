#pragma once

namespace hook {
    class menu_control_hook : public RE::MenuControls {
    public:
        static void install();

    private:
        static RE::BSEventNotifyControl process_event(RE::MenuControls* a_menuControls,
            RE::InputEvent* const* a_event,
            RE::BSTEventSource<RE::InputEvent*>* a_eventSource);

        static inline REL::Relocation<decltype(process_event)> process_event_;

        static bool is_menu_open(RE::UI*& a_ui);

        static void TweenMenu_CloseTweenMenu();
    };
}  // hook
