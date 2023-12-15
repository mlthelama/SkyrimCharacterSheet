#include "type_util.h"

namespace util {

    std::string type_util::get_float_as_string(float a_value) {
        return cut_string(fmt::format(FMT_STRING("{:.2f}"), a_value));
    }

    template <typename T>
    std::vector<T> type_util::get_vector_intersect(std::vector<T>& a_vector_first, std::vector<T>& a_vector_second) {
        std::vector<T> intersection_vector;

        std::ranges::sort(a_vector_first);
        std::ranges::sort(a_vector_second);

        std::ranges::set_intersection(a_vector_first, a_vector_second, back_inserter(intersection_vector));
        return intersection_vector;
    }

    std::string type_util::cut_string(const std::string& a_value) {
        std::string text;
        if (a_value.find('.') != std::string::npos) {
            if (auto s = a_value.substr(a_value.find('.') + 1, 2); std::ranges::count(s, '0') == 2) {
                text = a_value.substr(0, a_value.find('.'));
            } else {
                text = a_value.substr(0, a_value.find('.') + 3);
            }
        } else {
            text = a_value;
        }
        return text;
    }
}  // util
