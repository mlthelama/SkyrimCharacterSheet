#include "menu_key_input_holder.h"
#include "setting/input_setting.h"
#include "util/type_util.h"

namespace input {

    menu_key_input_holder* menu_key_input_holder::get_singleton() {
        static menu_key_input_holder singleton;
        return std::addressof(singleton);
    }

    std::set<uint32_t> menu_key_input_holder::get_open_key_combo() const { return open_key_combo_; }

    std::set<uint32_t> menu_key_input_holder::get_close_key_combo() const { return close_key_combo_; }

    std::set<uint32_t> menu_key_input_holder::get_inventory_open_key_combo() const { return inventory_open_key_combo_; }

    std::set<uint32_t> menu_key_input_holder::get_inventory_close_key_combo() const {
        return inventory_close_key_combo_;
    }

    void menu_key_input_holder::set_all() {
        open_key_combo_ = setting::input_setting::get_open_menu_key_combination();
        close_key_combo_ = setting::input_setting::get_close_menu_key_combination();
        inventory_open_key_combo_ = setting::input_setting::get_open_inventory_menu_key_combination();
        inventory_close_key_combo_ = setting::input_setting::get_close_inventory_menu_key_combination();
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

    void menu_key_input_holder::clear_set() { key_down_list_.clear(); }

    bool menu_key_input_holder::is_one_ignore_menu_open() {
        auto ignore_menu_list = setting::input_setting::get_ignore_input_menu_list();

        if (ignore_menu_list.empty()) {
            return false;
        }

        auto* ui = RE::UI::GetSingleton();
        auto open = false;
        for (auto& menu : ignore_menu_list) {
            open = ui->IsMenuOpen(menu);
            if (open) {
                logger::debug("menu {} is open {}"sv, menu, open);
                return open;
            }
        }

        return open;
    }

    bool menu_key_input_holder::is_down_list_equal(bool a_open, menu_type menu_type) {
        if (menu_type == menu_type::stats_inventory) {
            log_combo_set(a_open, menu_type);
            if (a_open) {
                return key_down_list_ == inventory_open_key_combo_;
            } else {
                return key_down_list_ == inventory_close_key_combo_;
            }
        } else {
            log_combo_set(a_open);
            if (a_open) {
                return key_down_list_ == open_key_combo_;
            } else {
                return key_down_list_ == close_key_combo_;
            }
        }
    }

    menu_key_input_holder::menu_key_input_holder() = default;

    void menu_key_input_holder::log_combo_set(bool a_open, menu_type menu_type) {
        if (menu_type == menu_type::stats_inventory) {
            logger::trace("key combo needed {}, down list {}"sv,
                util::type_util::get_delimited_string(a_open ? inventory_open_key_combo_ : inventory_close_key_combo_),
                util::type_util::get_delimited_string(key_down_list_));
        } else {
            logger::trace("key combo needed {}, down list {}"sv,
                util::type_util::get_delimited_string(a_open ? open_key_combo_ : close_key_combo_),
                util::type_util::get_delimited_string(key_down_list_));
        }
    }

}  // input
