#pragma once

inline static string cutString(string p_value)
{
	string text;
	if (p_value.find(".") != string::npos) {
		auto s = p_value.substr(p_value.find(".") + 1, 2);
		if (count(s.begin(), s.end(), '0') == 2) {
			text += p_value.substr(0, p_value.find("."));
		} else {
			text += p_value.substr(0, p_value.find(".") + 3);
		}
	} else {
		text += p_value;
	}
	return text;
}

inline static string getStringValueFromFloat(float p_x) {
	return to_string(round(p_x * 100.0) / 100.0);
}

inline static float calculateValue(float p_rm, float p_r) {
	return (p_rm * p_r) / 100;
}

inline static int64_t getMultiplier(int64_t p_mp) {
	if (p_mp < 0) {
		logger::warn("multiplier value {} not supported, using 1"sv, p_mp);
		return 1;
	} else {
		return p_mp;
	}
}

inline static MenuValue getMenu(int64_t p_menu_id) {
	//in case the config value does not match
	if (configMenu.find(p_menu_id) == configMenu.end()) {
		logger::warn("can not find Menu {}"sv, p_menu_id);
		return MenuValue::mNone;
	} else {
		return configMenu.find(p_menu_id)->second;
	}
}

template <typename T>
inline static string intToHex(T i) {
	stringstream stream;
	stream << "0x"
		   << setfill('0') << setw(sizeof(T) * 2)
		   << hex << i;

	return stream.str();
}