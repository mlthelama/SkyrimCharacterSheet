#include "quest.h"
#include "util/type_util.h"

namespace util {
    std::vector<uint16_t> quest::get_stages_if_complete(RE::TESQuest* a_quest) {
        std::vector<uint16_t> finished_stages;

        auto form_id = util::type_util::int_to_hex(a_quest->formID);
        logger::debug("quest name ({}), form id {}, priority {}"sv,
            a_quest->GetName(),
            form_id,
            a_quest->data.priority);

        logger::trace("executed stages for quest {}"sv, form_id);
        const auto executed_stages = a_quest->executedStages;
        for (auto it = executed_stages->begin(); it != executed_stages->end(); ++it) {
            const auto& [data] = *it;
            auto [index, flags, pad3, pad4] = data;
            logger::trace("index {}, flag {}"sv, index, flags.underlying());
            if (flags.underlying() == 1) {
                finished_stages.push_back(index);
            }
        }

        logger::trace("waiting stages for quest {}"sv, form_id);
        const auto waiting_stages = a_quest->waitingStages;
        for (auto it = waiting_stages->begin(); it != waiting_stages->end(); ++it) {
            const auto quest_stage = *it;
            auto [index, flags, pad3, pad4] = quest_stage->data;
            logger::trace("index {}, flag {}"sv, index, flags.underlying());
            if (flags.underlying() == 1) {
                finished_stages.push_back(index);
            }
        }
        return finished_stages;
    }

    bool quest::is_one_quest_stage_complete(RE::TESQuest* a_quest, std::vector<uint16_t> a_stages) {
        auto finished_stages = get_stages_if_complete(a_quest);
        auto intersect = type_util::get_vector_intersect(finished_stages, a_stages);
        auto form_id = util::type_util::int_to_hex(a_quest->formID);

        logger::debug("for quest {}, got stages (values)/size completed ({})/{}, given ({})/{}, intersect ({})/{}"sv,
            form_id,
            type_util::get_delimited_string(finished_stages),
            finished_stages.size(),
            type_util::get_delimited_string(a_stages),
            a_stages.size(),
            type_util::get_delimited_string(intersect),
            intersect.size());

        return !intersect.empty();
    }

    bool quest::is_quest_stage_complete(RE::TESQuest* a_quest, const uint16_t a_stage) {
        return is_one_quest_stage_complete(a_quest, std::vector{ a_stage });
    }

    bool quest::is_quest_stage_complete(const RE::FormID a_form_id, const uint16_t a_stage) {
        const auto quest = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
        return is_quest_stage_complete(quest, a_stage);
    }

    bool quest::is_one_quest_stage_complete(const RE::FormID a_form_id, const std::vector<uint16_t>& a_stages) {
        const auto quest = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
        return is_one_quest_stage_complete(quest, a_stages);
    }
}  // util
