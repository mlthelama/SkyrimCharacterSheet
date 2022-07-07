#pragma once

class champion {
    using value_string_map = std::map<FactionValue, std::string>;

public:
    static champion* get_singleton() {
        static champion singleton;
        return std::addressof(singleton);
    }

    std::string get_champion(const FactionValue a_stat) {
        if (!champion_list_.contains(a_stat)) {
            return "";
        }
        return champion_list_.find(a_stat)->second;
    }

    void get_champions() {
        champion_list_.clear();
        for (const auto& [fst, snd] : _championQuestStageMap) {
            auto champion_value = fst;
            for (const auto& [a_form_id, a_stages] : snd) {
                const auto qst = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
                logger::trace("Champion {} working with formid {}"sv,
                    champion_value,
                    string_util::int_to_hex(qst->GetFormID()));
                if ([[maybe_unused]] auto quest_done = quest_util::is_one_quest_stage_complete(qst, a_stages)) {
                    logger::trace("Champion of {}"sv, champion_value);
                    champion_list_.insert(
                        std::pair<FactionValue, std::string>(champion_value, const_static_display_value));
                }
            }
        }


        logger::trace("got {} items in champion list."sv, champion_list_.size());
        log_map();
    }

    void clear_list() { champion_list_.clear(); }

    champion(const champion&) = delete;
    champion(champion&&) = delete;

    champion& operator=(const champion&) = delete;
    champion& operator=(champion&&) = delete;

private:
    champion() = default;

    ~champion() = default;

    value_string_map champion_list_;

    /*
    azura, 00028AD6 100 -
    boethiah, 0004D8D6 50 100 -
    clavicusVile, 0001BFC4 200 205 -
    hermaeusMora, 0002D512 100 200 -
    hircine, 0002A49A 100 105 200 -
    malacath, 0003B681 200 -
    mehrunesDagon, 000240B8 100 -
    mephala, 0004A37B 60 80 -
    meridia, 0004E4E1 500 -
    molagBal, 00022F08 200 -
    namira, 0002C358 100 600 -
    nocturnal, 00021555 200 -
    peryite, 0008998D 100 -
    sanguine, 0001BB9B 200 -
    sheogorath, 0002AC68 200 -
    vaermina 000242AF 200 -
    */

    inline static std::map<FactionValue, std::map<RE::FormID, std::vector<uint16_t>>> _championQuestStageMap = {
        { FactionValue::azura, { { 0x00028AD6, std::vector{ quest_util::get_as(100) } } } },
        { FactionValue::boethiah, { { 0x0004D8D6, std::vector{ quest_util::get_as(50), quest_util::get_as(100) } } } },
        { FactionValue::clavicus_vile,
          { { 0x0001BFC4, std::vector{ quest_util::get_as(200), quest_util::get_as(205) } } } },
        { FactionValue::hermaeus_mora,
          { { 0x0002D512, std::vector{ quest_util::get_as(100), quest_util::get_as(200) } } } },
        { FactionValue::hircine, { { 0x0002A49A, std::vector{ quest_util::get_as(100), quest_util::get_as(105) } } } },
        { FactionValue::malacath, { { 0x0003B681, std::vector{ quest_util::get_as(200) } } } },
        { FactionValue::mehrunes_dagon, { { 0x000240B8, std::vector{ quest_util::get_as(100) } } } },
        { FactionValue::mephala, { { 0x0004A37B, std::vector{ quest_util::get_as(60), quest_util::get_as(80) } } } },
        { FactionValue::meridia, { { 0x0004E4E1, std::vector{ quest_util::get_as(500) } } } },
        { FactionValue::molagBal, { { 0x00022F08, std::vector{ quest_util::get_as(200) } } } },
        { FactionValue::namira, { { 0x0002C358, std::vector{ quest_util::get_as(100), quest_util::get_as(600) } } } },
        { FactionValue::nocturnal, { { 0x00021555, std::vector{ quest_util::get_as(200) } } } },
        { FactionValue::peryite, { { 0x0008998D, std::vector{ quest_util::get_as(100) } } } },
        { FactionValue::sanguine, { { 0x0001BB9B, std::vector{ quest_util::get_as(200) } } } },
        { FactionValue::sheogorath, { { 0x0002AC68, std::vector{ quest_util::get_as(200) } } } },
        { FactionValue::vaermina, { { 0x000242AF, std::vector{ quest_util::get_as(200) } } } },
    };

    void log_map() const {
        for (const auto& [fst, snd] : champion_list_) { logger::trace("champion {}, {}"sv, fst, snd); }
    }
};
