#pragma once

class GameSettings {
public:
    static GameSettings* GetSingleton() {
        static GameSettings singleton;
        return std::addressof(singleton);
    }

    void getAndSetSettings() {
        auto gameSetting = RE::GameSettingCollection::GetSingleton();
        maxArmorResistance = getFloatSetting("fMaxArmorRating", gameSetting);
        maxResistance = getFloatSetting("fPlayerMaxResistance", gameSetting);

        logger::debug("fMaxArmorRating {}, fPlayerMaxResistance {}"sv, maxArmorResistance, maxResistance);
    }

    float maxArmorResistance = -1;
    float maxResistance = -1;

private:
    float getFloatSetting(const char* a_name, RE::GameSettingCollection*& a_game_setting) {
        return a_game_setting->GetSetting(a_name)->GetFloat();
    }
};
