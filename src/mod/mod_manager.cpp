#include "mod_manager.h"
#include "armor_rating_rescaled_remake.h"

namespace mod {
    mod_manager* mod_manager::get_singleton() {
        static mod_manager singleton;
        return std::addressof(singleton);
    }

    void mod_manager::set_armor_rating_rescaled_remake(bool a_value) {
        armor_rating_rescaled_remake = a_value;
        logger::trace("set armor rating rescaled remake to {}"sv, armor_rating_rescaled_remake);
        if (armor_rating_rescaled_remake) {
            armor_rating_rescaled_remake::load_config();
        }
    }
    bool mod_manager::get_armor_rating_rescaled_remake() const { return armor_rating_rescaled_remake; }

    void mod_manager::set_hand_to_hand(bool a_value) {
        hand_to_hand = a_value;
        logger::trace("set hand to hand to {}"sv, hand_to_hand);
    }
    bool mod_manager::get_hand_to_hand() const { return hand_to_hand; }

    void mod_manager::set_skyrim_unbound(bool a_value) {
        skyrim_unbound = a_value;
        logger::trace("set skyrim unbound to {}"sv, skyrim_unbound);
    }
    bool mod_manager::get_skyrim_unbound() const { return skyrim_unbound; }

    void mod_manager::set_skyrim_souls(bool a_value) {
        skyrim_souls = a_value;
        logger::trace("set skyrim souls to {}"sv, skyrim_souls);
    }
    bool mod_manager::get_skyrim_souls() const { return skyrim_souls; }

    void mod_manager::set_blade_and_blunt(bool a_value) {
        blade_and_blunt = a_value;
        logger::trace("set blade and blunt to {}"sv, blade_and_blunt);
    }
    bool mod_manager::get_blade_and_blunt() const { return blade_and_blunt; }
}
