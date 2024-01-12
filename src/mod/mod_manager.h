#pragma once

namespace mod {
    class mod_manager {
    public:
        [[nodiscard]] static mod_manager* get_singleton();

        void set_armor_rating_rescaled_remake(bool a_value);
        [[nodiscard]] bool get_armor_rating_rescaled_remake() const;

        void set_hand_to_hand(bool a_value);
        [[nodiscard]] bool get_hand_to_hand() const;

        void set_skyrim_unbound(bool a_value);
        [[nodiscard]] bool get_skyrim_unbound() const;

        void set_skyrim_souls(bool a_value);
        [[nodiscard]] bool get_skyrim_souls() const;

        void set_blade_and_blunt(bool a_value);
        [[nodiscard]] bool get_blade_and_blunt() const;

        void set_wait_menu_redirected(bool a_value);
        [[nodiscard]] bool get_wait_menu_redirected() const;

    private:
        bool armor_rating_rescaled_remake{};
        bool hand_to_hand{};
        bool skyrim_unbound{};
        bool skyrim_souls{};
        bool blade_and_blunt{};
        bool wait_menu_redirected{};
    };
}
