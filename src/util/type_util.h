#pragma once

namespace util {
    class type_util {
    public:
        template <typename T>
        static std::string int_to_hex(T a_value) {
            std::stringstream stream;
            stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << a_value;

            return stream.str();
        }

        template <typename T>
        static std::string format_with_delimiter(float a_value_one, float a_value_two, T a_delimiter) {
            return fmt::format(FMT_STRING("{}{}{}"),
                get_float_as_string(a_value_one),
                a_delimiter,
                get_float_as_string(a_value_two));
        }

        template <typename T>
        static std::string get_delimited_string(std::vector<T>& a_vector) {
            auto delimited_string =
                a_vector.empty() ?
                    "" :
                    std::accumulate(std::begin(a_vector),
                        std::end(a_vector),
                        std::string{},
                        [](std::string r, const int p) { return std::move(r) + std::to_string(p) + ","; });
            if (!delimited_string.empty()) {
                delimited_string.pop_back();
            }
            return delimited_string;
        }
        
        template <typename T>
        static std::string get_delimited_string(std::set<T>& a_set) {
            auto delimited_string =
                a_set.empty() ?
                    "" :
                    std::accumulate(std::begin(a_set),
                        std::end(a_set),
                        std::string{},
                        [](std::string r, const int p) { return std::move(r) + std::to_string(p) + ","; });
            if (!delimited_string.empty()) {
                delimited_string.pop_back();
            }
            return delimited_string;
        }

        static std::string get_float_as_string(float a_value);

        template <typename T>
        static std::vector<T> get_vector_intersect(std::vector<T>& a_vector_first, std::vector<T>& a_vector_second) {
            std::vector<T> intersection_vector;

            std::ranges::sort(a_vector_first);
            std::ranges::sort(a_vector_second);

            std::ranges::set_intersection(a_vector_first, a_vector_second, back_inserter(intersection_vector));
            return intersection_vector;
        }
        
    private:
        static std::string cut_string(const std::string& a_value);
    };
}  // util
