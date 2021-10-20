#pragma once

class StatItem {
public:
    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending, bool p_show) {
        this->setName(p_name);
        this->setActor(p_actor);
        this->setDisplayName(p_display_name);
        this->setEnding(p_ending);
        this->setShow(p_show);
        this->setMenu(StatsMenuValue::mNone);

        this->setValue("");
        this->setGuiText("");

        this->logItem();
    }

    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending, bool p_show,
        StatsMenuValue p_menu) {
        this->setName(p_name);
        this->setActor(p_actor);
        this->setDisplayName(p_display_name);
        this->setEnding(p_ending);
        this->setShow(p_show);
        this->setMenu(p_menu);

        this->setValue("");
        this->setGuiText("");

        this->logItem();
    };

    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending, bool p_show,
        StatsMenuValue p_menu, int64_t p_value_multiplier) {
        this->setName(p_name);
        this->setActor(p_actor);
        this->setDisplayName(p_display_name);
        this->setEnding(p_ending);
        this->setShow(p_show);
        this->setMenu(p_menu);
        this->setValueMultiplier(p_value_multiplier);

        this->setValue("");
        this->setGuiText("");

        this->logItem();
    };


    void setName(StatsValue p_name) { name = p_name; }

    StatsValue getName() { return name; }

    void setActor(RE::ActorValue p_actor) { actor = p_actor; }

    RE::ActorValue getActor() { return actor; }

    void setValue(std::string p_value) {
        if (!p_value.empty()) {
            value = p_value;
            logger::trace("set Value {} for name {} display {}"sv, p_value, name, displayName);
            buildText();
        }
    }

    std::string getValue() { return value; }

    void setDisplayName(std::string p_display_name) { displayName = p_display_name; }

    std::string getDisplayName() { return displayName; }

    void setEnding(std::string p_ending) { ending = p_ending; }

    std::string getEnding() { return ending; }

    void setShow(bool p_show) { show = p_show; }

    bool getShow() { return show; }

    void setGuiText(std::string p_gui_text) { guiText = p_gui_text; }

    std::string getGuiText() { return guiText; }

    void setMenu(StatsMenuValue p_menu) { menu = p_menu; }

    StatsMenuValue getMenu() { return menu; }

    void setValueMultiplier(int64_t p_value_multiplier) { valueMultiplier = p_value_multiplier; }

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
