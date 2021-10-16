#include "data/factiondata.h"
#include "stats/champion.h"
#include "stats/faction.h"
#include "stats/factionfiller.h"
#include "stats/thane.h"

auto FactionData::GetSingleton() -> FactionData* {
    static FactionData singleton;
    return std::addressof(singleton);
}

std::vector<std::shared_ptr<FactionItem>> FactionData::getFactionValues() {
    logger::trace("Gather Values to Show ..."sv);

    auto player = RE::PlayerCharacter::GetSingleton();
    auto faction = Faction::GetSingleton();
    auto thane = Thane::GetSingleton();
    auto champion = Champion::GetSingleton();
    auto filler = FactionFiller::GetSingleton();

    if (*Settings::showFactions) {
        faction->getFactions(player);
    }
    if (*Settings::showThanes) {
        thane->getRegionThanes();
    }
    if (*Settings::showChampion) {
        champion->getChampions();
    }

    auto statList = filler->getData();
    for (auto& element : statList) {
        logger::trace("start working name {}, fill values, if needed ..."sv, element->getName());
        if (!element->getShow()) {
            continue;
        }

        switch (element->getName()) {
            case FactionValue::companions:
            case FactionValue::darkbrotherHood:
            case FactionValue::collegeOfWinterhold:
            case FactionValue::orcFriend:
            case FactionValue::thiefsGuild:
            case FactionValue::imperialLegion:
            case FactionValue::stormcloaks:
            case FactionValue::greybeard:
            case FactionValue::bard:
            case FactionValue::volkiharVampireClan:
            case FactionValue::dawnguard:
            case FactionValue::houseTelvanni:
                element->setValue(faction->getRank(element->getName()));
                break;
            case FactionValue::thaneOfEastmarch:
            case FactionValue::thaneOfFalkreath:
            case FactionValue::thaneOfHaafingar:
            case FactionValue::thaneOfHjaalmarch:
            case FactionValue::thaneOfThePale:
            case FactionValue::thaneOfTheReach:
            case FactionValue::thaneOfTheRift:
            case FactionValue::thaneOfWhiterun:
            case FactionValue::thaneOfWinterhold:
                element->setValue(thane->getThane(element->getName()));
                break;
            case FactionValue::azura:
            case FactionValue::boethiah:
            case FactionValue::clavicusVile:
            case FactionValue::hermaeusMora:
            case FactionValue::hircine:
            case FactionValue::malacath:
            case FactionValue::mehrunesDagon:
            case FactionValue::mephala:
            case FactionValue::meridia:
            case FactionValue::molagBal:
            case FactionValue::namira:
            case FactionValue::nocturnal:
            case FactionValue::peryite:
            case FactionValue::sanguine:
            case FactionValue::sheogorath:
            case FactionValue::vaermina:
                element->setValue(champion->getChampion(element->getName()));
                break;
            default:
                logger::warn("unhandeled stat, name {}, displayName {}"sv, element->getName(),
                    element->getDisplayName());
                break;
        }
    }

    filler->PrintFactionVector(statList);

    return statList;
}