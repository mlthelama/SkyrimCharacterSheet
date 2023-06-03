#pragma once

namespace util {
    class quest {
    public:
        static std::vector<uint16_t> get_stages_if_complete(RE::TESQuest* a_quest);

        static bool is_one_quest_stage_complete(RE::TESQuest* a_quest, std::vector<uint16_t> a_stages);

        static bool is_quest_stage_complete(RE::TESQuest* a_quest, uint16_t a_stage);

        static bool is_quest_stage_complete(RE::FormID a_form_id, uint16_t a_stage);

        static bool is_one_quest_stage_complete(RE::FormID a_form_id, const std::vector<uint16_t>& a_stages);
    };
}  // util
