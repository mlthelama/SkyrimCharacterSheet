﻿#include "menu_key_input_holder.h"
#include "setting/input_setting.h"
#include "util/type_util.h"

namespace input {

    menu_key_input_holder* menu_key_input_holder::get_singleton() {
        static menu_key_input_holder singleton;
        return std::addressof(singleton);
    }

    std::set<uint32_t> menu_key_input_holder::get_open_inventory_key_combo() const { return open_inventory_key_combo_; }

    std::set<uint32_t> menu_key_input_holder::get_close_inventory_key_combo() const {
        return close_inventory_key_combo_;
    }

    void menu_key_input_holder::set_all() {
        open_inventory_key_combo_ = setting::input_setting::get_open_inventory_menu_key_combination();
        close_inventory_key_combo_ = setting::input_setting::get_close_inventory_menu_key_combination();
    }

    void menu_key_input_holder::add_key_down(uint32_t a_key) {
        key_down_list_.insert(a_key);
        if (!key_down_list_.empty()) {
            logger::trace("size {}, down list {}"sv,
                key_down_list_.size(),
                util::type_util::get_delimited_string(key_down_list_));
        }
    }

    void menu_key_input_holder::remove_key_down(uint32_t a_key) {
        key_down_list_.erase(a_key);
        if (!key_down_list_.empty()) {
            logger::trace("size {}, down list {}"sv,
                key_down_list_.size(),
                util::type_util::get_delimited_string(key_down_list_));
        }
    }

    void menu_key_input_holder::set_menu_manual_close(bool a_down) { menu_manual_close = a_down; }

    bool menu_key_input_holder::get_menu_manual_close() const { return menu_manual_close; }

    bool menu_key_input_holder::is_down_list_equal(bool a_open) {
        log_combo_set(a_open);
        if (a_open) {
            return key_down_list_ == open_inventory_key_combo_;
        } else {
            return key_down_list_ == close_inventory_key_combo_;
        }
    }

    menu_key_input_holder::menu_key_input_holder() = default;

    void menu_key_input_holder::log_combo_set(bool a_open) {
        logger::trace("key combo needed {}, down list {}"sv,
            util::type_util::get_delimited_string(a_open ? open_inventory_key_combo_ : close_inventory_key_combo_),
            util::type_util::get_delimited_string(key_down_list_));
    }

}  // input