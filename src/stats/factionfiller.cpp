#pragma once
#include "stats/factionfiller.h"

using Menu = FactionMenuValue;

auto FactionFiller::GetSingleton() -> FactionFiller* {
    static FactionFiller singleton;
    return std::addressof(singleton);
}

std::vector<std::shared_ptr<FactionItem>> FactionFiller::getData() {
    std::vector<std::shared_ptr<FactionItem>> factionList = {
        std::make_shared<FactionItem>(FactionValue::darkbrotherHood, *Settings::darkbrotherHoodString,
            *Settings::showFactions, getFactionMenu(*Settings::darkbrotherHoodMenu)),
        std::make_shared<FactionItem>(FactionValue::thiefsGuild, *Settings::thiefsGuildString, *Settings::showFactions,
            getFactionMenu(*Settings::thiefsGuildMenu)),
        std::make_shared<FactionItem>(FactionValue::orcFriend, *Settings::orcFriendString, *Settings::showFactions,
            getFactionMenu(*Settings::orcFriendMenu)),
        std::make_shared<FactionItem>(FactionValue::collegeOfWinterhold, *Settings::collegeOfWinterholdString,
            *Settings::showFactions, getFactionMenu(*Settings::collegeOfWinterholdMenu)),
        std::make_shared<FactionItem>(FactionValue::companions, *Settings::companionsString, *Settings::showFactions,
            getFactionMenu(*Settings::companionsMenu)),
        std::make_shared<FactionItem>(FactionValue::imperialLegion, *Settings::imperialLegionString,
            *Settings::showFactions, getFactionMenu(*Settings::imperialLegionMenu)),
        std::make_shared<FactionItem>(FactionValue::stormcloaks, *Settings::stormcloaksString, *Settings::showFactions,
            getFactionMenu(*Settings::stormcloaksMenu)),
        std::make_shared<FactionItem>(FactionValue::greybeard, *Settings::greybeardString, *Settings::showFactions,
            getFactionMenu(*Settings::greybeardMenu)),
        std::make_shared<FactionItem>(FactionValue::bard, *Settings::bardString, *Settings::showFactions,
            getFactionMenu(*Settings::bardMenu)),
        std::make_shared<FactionItem>(FactionValue::volkiharVampireClan, *Settings::volkiharVampireClanString,
            *Settings::showFactions, getFactionMenu(*Settings::volkiharVampireClanMenu)),
        std::make_shared<FactionItem>(FactionValue::dawnguard, *Settings::dawnguardString, *Settings::showFactions,
            getFactionMenu(*Settings::dawnguardMenu)),
        std::make_shared<FactionItem>(FactionValue::houseTelvanni, *Settings::houseTelvanniString,
            *Settings::showFactions, getFactionMenu(*Settings::houseTelvanniMenu)),

        std::make_shared<FactionItem>(FactionValue::thaneOfEastmarch, *Settings::thaneOfEastmarchName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfEastmarchMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfFalkreath, *Settings::thaneOfFalkreathName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfFalkreathMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfHaafingar, *Settings::thaneOfHaafingarName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfHaafingarMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfHjaalmarch, *Settings::thaneOfHjaalmarchName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfHjaalmarchMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfThePale, *Settings::thaneOfThePaleName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfThePaleMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfTheReach, *Settings::thaneOfTheReachName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfTheReachMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfTheRift, *Settings::thaneOfTheRiftName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfTheRiftMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfWhiterun, *Settings::thaneOfWhiterunName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfWhiterunMenu), true),
        std::make_shared<FactionItem>(FactionValue::thaneOfWinterhold, *Settings::thaneOfWinterholdName,
            *Settings::showThanes, getFactionMenu(*Settings::thaneOfWinterholdMenu), true),
    };

    logger::debug("Vector Size is {}"sv, factionList.size());
    return factionList;
}

void FactionFiller::PrintFactionVector(std::vector<std::shared_ptr<FactionItem>>& p_vec) {
    logger::trace("Vector Size is {}"sv, p_vec.size());
    for (auto& element : p_vec) {
        logger::trace("name {}, value {}, displayname ({}), show {}, guiText ({}), menu {}, VID {}"sv,
            element->getName(), element->getValue(), element->getDisplayName(), element->getShow(),
            element->getGuiText(), element->getMenu(), element->getDisplayIsValue());
    }
}