#pragma once

class thane {
    using value_string_map = std::map<FactionValue, std::string>;

public:
    static thane* get_singleton() {
        static thane singleton;
        return std::addressof(singleton);
    }

    std::string get_thane(const FactionValue a_stat) {
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
                logger::trace("Thane {} working with formid {}"sv, thane_value, string_util::int_to_hex(qst));
                auto is_thane = false;

                const auto qst_done = quest_util::is_quest_stage_complete(qst, a_stage);

                if (thane_value == FactionValue::thane_of_eastmarch) {
                    const auto eastmarch_cw_quest = RE::TESForm::LookupByID(0x00035A23)->As<RE::TESQuest>();
                    const auto cw_object_quest = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>();


                    if (const auto pre_quests = (quest_util::is_one_quest_stage_complete(eastmarch_cw_quest,
                                                    std::vector{ quest_util::get_as(200), quest_util::get_as(255) })) ||
                                                (quest_util::is_one_quest_stage_complete(cw_object_quest,
                                                    std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) }));
                        pre_quests && qst_done) {
                        is_thane = true;
                    }
                } else if (thane_value == FactionValue::thane_of_whiterun && !*settings::skyrim_unbound) {
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
                    logger::trace("Thane of {}"sv, thane_value);
                    thane_list_.insert(std::pair<FactionValue, std::string>(thane_value, const_static_display_value));
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

    inline static std::map<FactionValue, std::map<RE::FormID, uint16_t>> thane_quest_stage_map_ = {
        { FactionValue::thane_of_eastmarch, { { 0x000A2CA6, quest_util::get_as(25) } } },
        { FactionValue::thane_of_falkreath, { { 0x000A34DE, quest_util::get_as(25) } } },
        { FactionValue::thane_of_haafingar, { { 0x000A2C9B, quest_util::get_as(25) } } },
        { FactionValue::thane_of_hjaalmarch, { { 0x000A34CE, quest_util::get_as(25) } } },
        { FactionValue::thane_of_the_pale, { { 0x000A34D4, quest_util::get_as(25) } } },
        { FactionValue::thane_of_the_reach, { { 0x000A2C86, quest_util::get_as(25) } } },
        { FactionValue::thane_of_the_rift, { { 0x00065BDF, quest_util::get_as(20) } } },  //rift quest is special
        { FactionValue::thane_of_whiterun,
            { { 0x000A2C9E,
                quest_util::get_as(25) } } },  //just if stormcloaks won the war, otherwise MQ104/0002610C/160
        { FactionValue::thane_of_winterhold, { { 0x000A34D7, quest_util::get_as(25) } } }
    };

    void log_map() const {
        for (const auto& [fst, snd] : thane_list_) { logger::trace("thane {}, {}"sv, fst, snd); }
    }
};
