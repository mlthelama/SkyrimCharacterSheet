#pragma once

namespace StringUtil {
    static std::string cutString(std::string a_value) {
        std::string text;
        if (a_value.find(".") != std::string::npos) {
            auto s = a_value.substr(a_value.find(".") + 1, 2);
            if (count(s.begin(), s.end(), '0') == 2) {
                text = a_value.substr(0, a_value.find("."));
            } else {
                text = a_value.substr(0, a_value.find(".") + 3);
            }
        } else {
            text = a_value;
        }
        return text;
    }

    static std::string getStringValueFromFloat(float a_x) { return cutString(fmt::format(FMT_STRING("{:.2f}"), a_x)); }

    static float calculateValue(float a_rm, float a_r) { return (a_rm * a_r) / 100; }

    template <typename T>
    static std::string intToHex(T a_i) {
        std::stringstream stream;
        stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << a_i;

        return stream.str();
    }
}

namespace MenuUtil {
    static enum class ShowMenu { mStats, mFaction, mInventoryStats };

    static std::map<ShowMenu, std::string_view> menuName = {
        { ShowMenu::mStats, static_cast<std::string_view>(*Settings::showStatsTitleTitle) },
        { ShowMenu::mFaction, static_cast<std::string_view>(*Settings::showFactionsTitleTitle) },
        { ShowMenu::mInventoryStats, static_cast<std::string_view>(*Settings::showStatsInventoryTitleTitle) }
    };

    static enum class StatsMenuValue {
        mNone = 0,
        mPlayer = 1,
        mDefence = 2,
        mAttack = 3,
        mMagic = 4,
        mWarrior = 5,
        mThief = 6
    };

    /* config can not work with enums, so lets map it*/
    inline static std::map<int64_t, StatsMenuValue> _constConfigStatsMenu = {
        { static_cast<int64_t>(StatsMenuValue::mNone), StatsMenuValue::mNone },
        { static_cast<int64_t>(StatsMenuValue::mPlayer), StatsMenuValue::mPlayer },
        { static_cast<int64_t>(StatsMenuValue::mDefence), StatsMenuValue::mDefence },
        { static_cast<int64_t>(StatsMenuValue::mAttack), StatsMenuValue::mAttack },
        { static_cast<int64_t>(StatsMenuValue::mMagic), StatsMenuValue::mMagic },
        { static_cast<int64_t>(StatsMenuValue::mWarrior), StatsMenuValue::mWarrior },
        { static_cast<int64_t>(StatsMenuValue::mThief), StatsMenuValue::mThief },
    };

    static enum class FactionMenuValue { mNone = 0, mFaction = 1, mThane = 2, mChampion = 3 };

    /* config can not work with enums, so lets map it*/
    inline static std::map<int64_t, FactionMenuValue> _constConfigFactionMenu = {
        { static_cast<int64_t>(FactionMenuValue::mNone), FactionMenuValue::mNone },
        { static_cast<int64_t>(FactionMenuValue::mFaction), FactionMenuValue::mFaction },
        { static_cast<int64_t>(FactionMenuValue::mThane), FactionMenuValue::mThane },
        { static_cast<int64_t>(FactionMenuValue::mChampion), FactionMenuValue::mChampion },
    };

    static enum class StatsInventoryMenuValue { mNone = 0, mArmor = 1, mWeapon = 2, mEffect = 3 };

    /* config can not work with enums, so lets map it*/
    inline static std::map<int64_t, StatsInventoryMenuValue> _constConfigStatsInventoryMenu = {
        { static_cast<int64_t>(StatsInventoryMenuValue::mNone), StatsInventoryMenuValue::mNone },
        { static_cast<int64_t>(StatsInventoryMenuValue::mArmor), StatsInventoryMenuValue::mArmor },
        { static_cast<int64_t>(StatsInventoryMenuValue::mWeapon), StatsInventoryMenuValue::mWeapon },
        { static_cast<int64_t>(StatsInventoryMenuValue::mEffect), StatsInventoryMenuValue::mEffect },
    };

    static std::string_view getMenuName(ShowMenu a_menu) {
        if (menuName.find(a_menu) == menuName.end()) {
            logger::warn("can not find Name for Menu {}"sv, a_menu);
            return "";
        } else {
            return menuName.find(a_menu)->second;
        }
    }

    static StatsMenuValue getStatsMenu(int64_t a_menu_id) {
        //in case the config value does not match
        if (_constConfigStatsMenu.find(a_menu_id) == _constConfigStatsMenu.end()) {
            logger::warn("({}) can not find Menu {}"sv, getMenuName(ShowMenu::mStats), a_menu_id);
            return StatsMenuValue::mNone;
        } else {
            return _constConfigStatsMenu.find(a_menu_id)->second;
        }
    }

    static FactionMenuValue getFactionMenu(int64_t a_menu_id) {
        //in case the config value does not match
        if (_constConfigFactionMenu.find(a_menu_id) == _constConfigFactionMenu.end()) {
            logger::warn("({}) can not find Menu {}"sv, getMenuName(ShowMenu::mFaction), a_menu_id);
            return FactionMenuValue::mNone;
        } else {
            return _constConfigFactionMenu.find(a_menu_id)->second;
        }
    }

    static StatsInventoryMenuValue getStatsInventoryMenu(int64_t a_menu_id) {
        //in case the config value does not match
        if (_constConfigStatsInventoryMenu.find(a_menu_id) == _constConfigStatsInventoryMenu.end()) {
            logger::warn("({}) can not find Menu {}"sv, getMenuName(ShowMenu::mInventoryStats), a_menu_id);
            return StatsInventoryMenuValue::mNone;
        } else {
            return _constConfigStatsInventoryMenu.find(a_menu_id)->second;
        }
    }

    static std::string_view getNextMenuName(ShowMenu a_menu) {
        //if cast to an int value outside the enum it should be _constUndefined
        return getMenuName(static_cast<ShowMenu>(static_cast<int>(a_menu) + 1));
    }

    static std::string_view getPrevMenuName(ShowMenu a_menu) {
        //if cast to an int value outside the enum it should be _constUndefined
        return getMenuName(static_cast<ShowMenu>(static_cast<int>(a_menu) - 1));
    }

    static std::string buildDisplayString(std::string a_value,
        std::string a_display_name,
        std::string a_ending,
        bool a_show,
        bool a_value_is_display) {
        if (!a_value.empty() && !a_display_name.empty() && !a_show) {
            return "";
        }

        std::string guiText;

        if (a_value_is_display) {
            if (a_value == _constStaticDisplayValue) {
                guiText = a_display_name;
            }
        } else {
            auto seperator = (a_value.size() > 0) ? ": " : "";
            guiText = fmt::format(FMT_STRING("{}{}{}{}"), a_display_name, seperator, a_value, a_ending);
        }

        return guiText;
    }

    static void logResolution() {
        const auto* const state = RE::BSGraphics::State::GetSingleton();
        logger::trace("Screen Resolution {}x{}"sv, state->screenWidth, state->screenHeight);
    }
    static int64_t getMultiplier(int64_t a_mp) {
        if (a_mp < 0) {
            logger::warn("multiplier value {} not supported, using 1"sv, a_mp);
            return 1;
        } else {
            return a_mp;
        }
    }
}

namespace ValueUtil {
    static float calculateArmorDamageRes(float a_armor_rating, int32_t a_pieces_worn) {
        return (float(a_armor_rating * 0.12) + float(3 * a_pieces_worn));
    }

    static std::string getValueWithCapIfNeeded(float a_res, float a_cap, std::string a_ending) {
        auto value = StringUtil::getStringValueFromFloat(a_res);

        if (a_res > a_cap) {
            value = fmt::format(FMT_STRING("{}{} ({})"),
                StringUtil::getStringValueFromFloat(a_cap),
                a_ending,
                StringUtil::getStringValueFromFloat(a_res));
        }
        return value;
    }
}

namespace VectorUtil {
    static std::vector<uint32_t> getIntersect(std::vector<uint32_t>& a_vec_first, std::vector<uint32_t>& a_vec_second) {
        std::vector<uint32_t> intersectionVector;

        std::sort(a_vec_first.begin(), a_vec_first.end());
        std::sort(a_vec_second.begin(), a_vec_second.end());

        std::set_intersection(a_vec_first.begin(),
            a_vec_first.end(),
            a_vec_second.begin(),
            a_vec_second.end(),
            back_inserter(intersectionVector));
        return intersectionVector;
    }

    static std::string getDelimitedString(std::vector<uint32_t>& a_vec) {
        auto deliString =
            a_vec.empty() ?
                "" :
                std::accumulate(std::begin(a_vec), std::end(a_vec), std::string{}, [](std::string r, int p) {
                    return std::move(r) + std::to_string(p) + ",";
                });

        if (!deliString.empty()) {
            deliString.pop_back();
        }
        return deliString;
    }
}

namespace QuestUtil {
    static std::vector<uint32_t> getStagesIfComplete(RE::TESQuest* a_quest) {
        std::vector<uint32_t> finStages;

        //all favour quests finish at 25 execpt rift = 20
        auto hex = StringUtil::intToHex(a_quest->GetFormID());
        //auto complete = false;
        logger::debug("Questname ({}), formid {}, prio {}"sv, a_quest->GetName(), hex, a_quest->data.priority);

        //todo make util function if for checking stages
        logger::trace("executed Stages for quest {}"sv, hex);
        auto exec = a_quest->executedStages;
        for (auto it = exec->begin(); it != exec->end(); ++it) {
            auto i = *it;
            auto qstdata = i.data;
            logger::trace("index {}, flag {}"sv, 1);
            //if (qstdata.flags.get() == RE::QUEST_STAGE_DATA::Flag::kStartUpStage) {
            if (qstdata.flags.underlying() == 1) {
                finStages.push_back(static_cast<uint32_t>(qstdata.index));
            }
        }

        logger::trace("waiting Stages for quest {}"sv, hex);
        auto waiting = a_quest->waitingStages;
        for (auto it = waiting->begin(); it != waiting->end(); ++it) {
            auto i = *it;
            auto qstdata = i->data;
            logger::trace("index {}, flag {}"sv, qstdata.index, qstdata.flags.get());
            if (qstdata.flags.underlying() == 1) {
                finStages.push_back(static_cast<uint32_t>(qstdata.index));
            }
        }
        return finStages;
    }

    static bool isOneQuestStageComplete(RE::TESQuest* a_quest, std::vector<uint32_t> a_stages) {
        auto finStages = getStagesIfComplete(a_quest);
        auto intersect = VectorUtil::getIntersect(finStages, a_stages);
        auto hex = StringUtil::intToHex(a_quest->GetFormID());

        logger::debug("For Quest {}, got Stages (Values)/size completed ({})/{}, given ({})/{}, intersect ({})/{}"sv,
            hex,
            VectorUtil::getDelimitedString(finStages),
            finStages.size(),
            VectorUtil::getDelimitedString(a_stages),
            a_stages.size(),
            VectorUtil::getDelimitedString(intersect),
            intersect.size());

        return intersect.size() > 0 ? true : false;
    }

    static bool isQuestStageComplete(RE::TESQuest* a_quest, uint32_t a_stage) {
        return isOneQuestStageComplete(a_quest, std::vector{ a_stage });
    }

    static bool isQuestStageComplete(RE::FormID a_form_id, uint32_t a_stage) {
        auto qst = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
        return isQuestStageComplete(qst, a_stage);
    }

    static bool isOneQuestStageComplete(RE::FormID a_form_id, std::vector<uint32_t> a_stages) {
        auto qst = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
        return isOneQuestStageComplete(qst, a_stages);
    }

    static uint32_t getAs(int a_i) { return static_cast<uint32_t>(a_i); }
}
