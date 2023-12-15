#pragma once

namespace menu_keys {
    //TODO put keys into config
    //Show Stats
    constexpr auto player_title = "$ShowStatsPlayerTitle"sv;
    constexpr auto attack_title = "$ShowStatsAttackTitle"sv;
    constexpr auto defence_title = "$ShowStatsDefenceTitle"sv;
    constexpr auto magic_title = "$ShowStatsMagicTitle"sv;
    constexpr auto thief_title = "$ShowStatsThiefTitle"sv;
    constexpr auto warrior_title = "$ShowStatsWarriorTitle"sv;

    //Show Factions
    constexpr auto faction_title = "$ShowFactionsFactionTitle"sv;
    constexpr auto thane_title = "$ShowFactionsThaneTitle"sv;
    constexpr auto champion_title = "$ShowFactionsChampionTitle"sv;

    //Show Stats Inventory
    constexpr auto equip_title = "$ShowStatsInventoryEquipmentTitle"sv;
    constexpr auto armor_title = "$ShowStatsInventoryArmorTitle"sv;
    constexpr auto weapon_title = "$ShowStatsInventoryWeaponTitle"sv;
    constexpr auto effect_title = "$ShowStatsInventoryEffectTitle"sv;

    constexpr auto vampire = "$ShowVampire"sv;
    constexpr auto werewolf = "$ShowWerewolf"sv;

    constexpr auto count = "$ShowCount"sv;


}
