#pragma once
#include "setting/data/menu_data.h"

namespace input {
    class menu_key_input_holder {
    public:
        using menu_type = setting_data::menu_data::menu_type;

        [[nodiscard]] static menu_key_input_holder* get_singleton();

        [[nodiscard]] std::set<uint32_t> get_open_key_combo() const;
        [[nodiscard]] std::set<uint32_t> get_close_key_combo() const;

        [[nodiscard]] std::set<uint32_t> get_inventory_open_key_combo() const;
        [[nodiscard]] std::set<uint32_t> get_inventory_close_key_combo() const;

        void set_all();

        void add_key_down(uint32_t a_key);
        void remove_key_down(uint32_t a_key);

        bool is_down_list_equal(bool a_open, menu_type menu_type = menu_type::stats);

        void set_menu_manual_close(bool a_down);

        [[nodiscard]] bool get_menu_manual_close() const;

        void clear_set();

        static bool is_one_ignore_menu_open();

        menu_key_input_holder(const menu_key_input_holder&) = delete;
        menu_key_input_holder(menu_key_input_holder&&) = delete;
        menu_key_input_holder& operator=(const menu_key_input_holder&) = delete;
        menu_key_input_holder& operator=(menu_key_input_holder&&) = delete;

    private:
        menu_key_input_holder();
        ~menu_key_input_holder() = default;

        std::set<uint32_t> key_down_list_;

        std::set<uint32_t> open_key_combo_;
        std::set<uint32_t> close_key_combo_;

        std::set<uint32_t> inventory_open_key_combo_;
        std::set<uint32_t> inventory_close_key_combo_;

        bool menu_manual_close = false;

        void log_combo_set(bool a_open, menu_type menu_type = menu_type::stats);
    };
}  // input
