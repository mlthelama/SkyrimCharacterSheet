#pragma once

class thane {
    using value_string_map = std::map<faction_value, std::string>;

public:
    static thane* get_singleton() {
        static thane singleton;
        return std::addressof(singleton);
    }

    [[nodiscard]] std::string get_thane(const faction_value a_stat) const {
        if (!thane_list_.contains(a_stat)) {
            return "";
        }
        return thane_list_.find(a_stat)->second;
    }

    void get_region_thanes() {
        clear_list();
        for (const auto& [fst, snd] : thane_quest_stage_map_) {
            auto thane_value = fst;
            for (const auto& [a_form_id, a_stage] : snd) {
                const auto qst = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
                logger::trace("Thane {} working with formid {}"sv,
                    string_util::get_int_from_enum(thane_value),
                    string_util::int_to_hex(qst));
                auto is_thane = false;

                const auto qst_done = quest_util::is_quest_stage_complete(qst, a_stage);

                if (thane_value == faction_value::windhelm) {
                    const auto eastmarch_cw_quest = RE::TESForm::LookupByID(0x00035A23)->As<RE::TESQuest>();
                    const auto cw_object_quest = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>();


                    if (const auto pre_quests = (quest_util::is_one_quest_stage_complete(eastmarch_cw_quest,
                                                    std::vector{ quest_util::get_as(200), quest_util::get_as(255) })) ||
                                                (quest_util::is_one_quest_stage_complete(cw_object_quest,
                                                    std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) }));
                        pre_quests && qst_done) {
                        is_thane = true;
                    }
                } else if (thane_value == faction_value::whiterun && !setting::get_skyrim_unbound()) {
                    const auto dragons_rising_qst = RE::TESForm::LookupByID(0x0002610C)->As<RE::TESQuest>();
                    const auto cw_object_qst = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>();
                    const auto pre_quests = quest_util::is_one_quest_stage_complete(cw_object_qst,
                        std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) });

                    if (const auto dragon_rising = quest_util::is_one_quest_stage_complete(dragons_rising_qst,
                            std::vector{ quest_util::get_as(160) });
                        (dragon_rising) || (pre_quests && qst_done)) {
                        is_thane = true;
                    }
                } else if (qst_done) {
                    is_thane = qst_done;
                }

                if (is_thane) {
                    logger::trace("Thane of {}"sv, string_util::get_int_from_enum(thane_value));
                    thane_list_.insert(std::pair(thane_value, get_thane_title_value(thane_value)));
                }
            }
        }

        logger::trace("got {} items in thane list."sv, thane_list_.size());
        log_map();
    }

    void clear_list() { thane_list_.clear(); }


    thane(const thane&) = delete;
    thane(thane&&) = delete;

    thane& operator=(const thane&) = delete;
    thane& operator=(thane&&) = delete;

private:
    thane() = default;

    ~thane() = default;

    value_string_map thane_list_;

    inline static std::map<faction_value, std::map<RE::FormID, uint16_t>> thane_quest_stage_map_ = {
        { faction_value::windhelm, { { 0x000A2CA6, quest_util::get_as(25) } } },
        { faction_value::falkreath, { { 0x000A34DE, quest_util::get_as(25) } } },
        { faction_value::solitude, { { 0x000A2C9B, quest_util::get_as(25) } } },
        { faction_value::morthal, { { 0x000A34CE, quest_util::get_as(25) } } },
        { faction_value::dawnstar, { { 0x000A34D4, quest_util::get_as(25) } } },
        { faction_value::markarth, { { 0x000A2C86, quest_util::get_as(25) } } },
        { faction_value::riften, { { 0x00065BDF, quest_util::get_as(20) } } },  //rift quest is special
        { faction_value::whiterun, { { 0x000A2C9E, quest_util::get_as(25) } } },
        //just if stormcloaks won the war, otherwise MQ104/0002610C/160
        { faction_value::winterhold, { { 0x000A34D7, quest_util::get_as(25) } } }
    };

    void log_map() const {
        for (const auto& [fst, snd] : thane_list_) {
            logger::trace("thane {}, {}"sv, string_util::get_int_from_enum(fst), snd);
        }
    }

    inline static std::map<faction_value, std::string_view> capital_to_title_ = { { faction_value::windhelm,
                                                                                      menu_keys::thane_of_eastmarch },
        { faction_value::falkreath, menu_keys::thane_of_falkreath },
        { faction_value::solitude, menu_keys::thane_of_haafinger },
        { faction_value::morthal, menu_keys::thane_of_hjaalmarch },
        { faction_value::dawnstar, menu_keys::thane_of_the_pale },
        { faction_value::markarth, menu_keys::thane_of_the_reach },
        { faction_value::riften, menu_keys::thane_of_the_rift },
        { faction_value::whiterun, menu_keys::thane_of_whiterun },
        { faction_value::winterhold, menu_keys::thane_of_winterhold } };

    static std::string_view get_thane_title_value(const faction_value a_faction_value) {
        return capital_to_title_.find(a_faction_value)->second;
    }
};
