#include "type_util.h"

namespace util {

    std::string type_util::get_float_as_string(float a_value) {
        return cut_string(fmt::format(FMT_STRING("{:.2f}"), a_value));
    }

    float type_util::calculate_value(const float a_rate_multiplier, const float a_rate) {
        return (a_rate_multiplier * a_rate) / 100;
    }

    std::string type_util::concat_string(std::string& a_value, std::string& a_ending) {
        return fmt::format(FMT_STRING("{}{}"), a_value, a_ending);
    }

    std::string type_util::get_format_value(float& a_resistance, float& a_max_resistance, std::string& a_ending) {
        auto string_value = string_util::get_string_value_from_float(a_resistance);

        if (a_resistance > a_max_resistance) {
            string_value = fmt::format(FMT_STRING("{}{} ({})"),
                string_util::get_string_value_from_float(a_resistance),
                a_ending,
                string_util::get_string_value_from_float(a_max_resistance));
        }
        return string_value;
    }

    template <typename T>
    std::vector<T> type_util::get_vector_intersect(std::vector<T>& a_vector_first, std::vector<T>& a_vector_second) {
        std::vector<T> intersection_vector;

        std::ranges::sort(a_vector_first);
        std::ranges::sort(a_vector_second);

        std::ranges::set_intersection(a_vector_first, a_vector_second, back_inserter(intersection_vector));
        return intersection_vector;
    }

    //TODO
    std::string type_util::cut_string(const std::string& a_value) {
        std::string text;
        if (a_value.find(".") != std::string::npos) {
            if (auto s = a_value.substr(a_value.find(".") + 1, 2); std::ranges::count(s, '0') == 2) {
                text = a_value.substr(0, a_value.find("."));
            } else {
                text = a_value.substr(0, a_value.find(".") + 3);
            }
        } else {
            text = a_value;
        }
        return text;
    }
}  // util
