#pragma once

class civil_war {
public:
    static civil_war* get_singleton() {
        static civil_war singleton;
        return std::addressof(singleton);
    }

    //handle jagged crown switch
    [[nodiscard]] std::string get_imperial_legion_rank() const {
        auto rank_name = const_string_empty_;
        for (const auto& [fst, snd] : imperial_quest_stage_map_) {
            const auto rank_value = fst;
            logger::trace("Checking Imperal Rank {}"sv, get_imperial_rank_name(rank_value));
            auto rank_done = false;
            for (const auto& [a_form_id, a_stages] : snd) {
                auto qst_done = quest_util::is_one_quest_stage_complete(a_form_id, a_stages);
                logger::trace("checked quest {}, done {}"sv, string_util::int_to_hex(a_form_id), qst_done);
                if (!qst_done) {
                    rank_done = false;
                    break;
                }
                rank_done = qst_done;
            }
            if (rank_done) {
                logger::trace("Imperial Rank {} done."sv, get_imperial_rank_name(rank_value));
                rank_name = get_imperial_rank_name(rank_value);
            } else {
                break;
            }
        }
        logger::trace("Check Done Rank {}"sv, rank_name);
        return rank_name;
    }

    //handle jagged crown switch
    [[nodiscard]] std::string get_stormcloak_rank() const {
        auto rank_name = const_string_empty_;
        for (const auto& [fst, snd] : stormcloak_quest_stage_map_) {
            const auto rank_value = fst;
            logger::trace("Checking Stormcloak Rank {}"sv, get_stormcloak_rank_name(rank_value));
            auto rank_done = false;
            for (const auto& [a_form_id, a_stages] : snd) {
                auto qst_done = quest_util::is_one_quest_stage_complete(a_form_id, a_stages);
                logger::trace("checked quest {}, done {}"sv, string_util::int_to_hex(a_form_id), qst_done);
                if (!qst_done) {
                    rank_done = false;
                    break;
                }
                rank_done = qst_done;
            }
            if (rank_done) {
                logger::trace("Stormcloak Rank {} done."sv, get_stormcloak_rank_name(rank_value));
                rank_name = get_stormcloak_rank_name(rank_value);
            } else {
                break;
            }
        }
        logger::trace("Check Done Rank {}"sv, rank_name);
        return rank_name;
    }

    civil_war(const civil_war&) = delete;
    civil_war(civil_war&&) = delete;

    civil_war& operator=(const civil_war&) = delete;
    civil_war& operator=(civil_war&&) = delete;

private:
    civil_war() = default;

    ~civil_war() = default;

    const std::string const_string_empty_;

    enum class imperial_rank {
        auxiliary,
        quaestor,
        praefect,
        tribune,
        legate,
    };

    inline static std::map<imperial_rank, std::string_view> imperial_rank_name_map_ = { { imperial_rank::auxiliary,
                                                                                            menu_keys::auxiliary },
        { imperial_rank::quaestor, menu_keys::quaestor },
        { imperial_rank::praefect, menu_keys::praefect },
        { imperial_rank::tribune, menu_keys::tribune },
        { imperial_rank::legate, menu_keys::legate } };

    static std::string_view get_imperial_rank_name(imperial_rank a_rank) {
        if (!imperial_rank_name_map_.contains(a_rank)) {
            logger::warn("can not find Name for Rank {}"sv, string_util::get_int_from_enum(a_rank));
            return "";
        }
        return imperial_rank_name_map_.find(a_rank)->second;
    }

    inline static std::map<imperial_rank, std::map<RE::FormID, std::vector<uint16_t>>> imperial_quest_stage_map_ = {
        { imperial_rank::auxiliary, { { 0x000D517A, std::vector{ quest_util::get_as(200) } } } },
        { imperial_rank::quaestor,
            { { 0x00096E71, std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) } } } },
        { imperial_rank::praefect,
            { { 0x0003BCC4, std::vector{ quest_util::get_as(200), quest_util::get_as(255) } },
                { 0x00083042, std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) } } } },
        { imperial_rank::tribune,
            { { 0x000504F0, std::vector{ quest_util::get_as(200), quest_util::get_as(255) } },
                { 0x00083042, std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) } } } },
        { imperial_rank::legate, { { 0x00035A23, std::vector{ quest_util::get_as(200), quest_util::get_as(255) } } } },
    };


    enum class stormcloak_rank {
        unblooded,
        ice_veins,
        bone_breaker,
        snow_hammer,
        stormblade,
    };

    inline static std::map<stormcloak_rank, std::string_view> stormcloak_rank_name_map_ = {
        { stormcloak_rank::unblooded, menu_keys::unblooded },
        { stormcloak_rank::ice_veins, menu_keys::ice_veins },
        { stormcloak_rank::bone_breaker, menu_keys::bone_breaker },
        { stormcloak_rank::snow_hammer, menu_keys::snow_hammer },
        { stormcloak_rank::stormblade, menu_keys::stormblade }
    };

    static std::string_view get_stormcloak_rank_name(const stormcloak_rank a_rank) {
        if (!stormcloak_rank_name_map_.contains(a_rank)) {
            logger::warn("can not find Name for Rank {}"sv, string_util::get_int_from_enum(a_rank));
            return "";
        }
        return stormcloak_rank_name_map_.find(a_rank)->second;
    }

    inline static std::map<stormcloak_rank, std::map<RE::FormID, std::vector<uint16_t>>> stormcloak_quest_stage_map_ = {
        { stormcloak_rank::unblooded, { { 0x000E2D29, std::vector{ quest_util::get_as(200) } } } },
        { stormcloak_rank::ice_veins,
            { { 0x00096E71, std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) } } } },
        { stormcloak_rank::bone_breaker,
            { { 0x00035A23, std::vector{ quest_util::get_as(200), quest_util::get_as(255) } } } },
        { stormcloak_rank::snow_hammer,
            { { 0x000504F0, std::vector{ quest_util::get_as(200), quest_util::get_as(255) } },
                { 0x00083042, std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) } } } },
        { stormcloak_rank::stormblade,
            { { 0x0003BCC4, std::vector{ quest_util::get_as(200), quest_util::get_as(255) } },
                { 0x00083042, std::vector{ quest_util::get_as(9000), quest_util::get_as(9999) } } } },
    };
};
