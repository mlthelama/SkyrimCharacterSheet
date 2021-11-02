#pragma once

class StatItem {
public:
    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending, bool p_show) :
        name(p_name), actor(p_actor), displayName(p_display_name), ending(p_ending), show(p_show),
        menu(StatsMenuValue::mNone), value(""), guiText("") {
        this->logItem();
    }

    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending, bool p_show,
        StatsMenuValue p_menu) :
        name(p_name),
        actor(p_actor), displayName(p_display_name), ending(p_ending), show(p_show), menu(p_menu), value(""),
        guiText("") {
        this->logItem();
    }

    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending, bool p_show,
        StatsMenuValue p_menu, int64_t p_value_multiplier) :
        name(p_name),
        actor(p_actor), displayName(p_display_name), ending(p_ending), show(p_show), menu(p_menu), value(""),
        guiText(""), valueMultiplier(p_value_multiplier) {
        this->logItem();
    }

    StatsValue getName() { return name; }

    RE::ActorValue getActor() { return actor; }

    void setValue(std::string p_value) {
        if (!p_value.empty()) {
            value = p_value;
            logger::trace("set Value {} for name {} display {}"sv, p_value, name, displayName);
            buildText();
        }
    }

    std::string getValue() { return value; }

    std::string getDisplayName() { return displayName; }

    std::string getEnding() { return ending; }

    bool getShow() { return show; }

    std::string getGuiText() { return guiText; }

    StatsMenuValue getMenu() { return menu; }

    int64_t getValueMultiplier() { return valueMultiplier; }

    StatItem() = delete;
    StatItem(const StatItem&) = default;
    StatItem(StatItem&&) = delete;

    ~StatItem() = default;

    StatItem& operator=(const StatItem&) = default;
    StatItem& operator=(StatItem&&) = delete;

private:
    StatsValue name;
    RE::ActorValue actor;
    std::string value;
    std::string displayName;
    std::string ending;
    bool show;
    std::string guiText;
    StatsMenuValue menu = StatsMenuValue::mNone;
    int64_t valueMultiplier = 1;

    void buildText() { guiText = buildDisplayString(value, displayName, ending, show, false); }

    void logItem() {
        logger::trace(
            "name {}, actor {}, value {}, displayname ({}), ending {}, show {}, guiText ({}), menu {}, VMP {}"sv, name,
            actor, value, displayName, ending, show, guiText, menu, valueMultiplier);
    }
};
