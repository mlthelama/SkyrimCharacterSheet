#pragma once
#include "menukeys.h"
#include "mod/armor_rating_rescaled_remake.h"
#include "mod/mod_manager.h"
#include "setting/game_setting.h"


namespace vector_util {
    static std::vector<uint16_t> get_intersect(std::vector<uint16_t>& a_vec_first,
        std::vector<uint16_t>& a_vec_second) {
        std::vector<uint16_t> intersection_vector;

        std::ranges::sort(a_vec_first);
        std::ranges::sort(a_vec_second);

        std::ranges::set_intersection(a_vec_first, a_vec_second, back_inserter(intersection_vector));
        return intersection_vector;
    }

    template <typename T>
    static std::string get_delimited_string(std::vector<T>& a_vec) {
        auto deli_string =
            a_vec.empty() ?
                "" :
                std::accumulate(std::begin(a_vec), std::end(a_vec), std::string{}, [](std::string r, const int p) {
                    return std::move(r) + std::to_string(p) + ",";
                });

        if (!deli_string.empty()) {
            deli_string.pop_back();
        }
        return deli_string;
    }
}
