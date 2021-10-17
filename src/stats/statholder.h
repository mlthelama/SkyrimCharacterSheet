#pragma once

class StatItem {
public:
    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending,
        boolean p_show);

    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending,
        boolean p_show, StatsMenuValue p_menu);

    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending,
        boolean p_show, StatsMenuValue p_menu, boolean p_static_text);

    StatItem(StatsValue p_name, RE::ActorValue p_actor, std::string p_display_name, std::string p_ending,
        boolean p_show, StatsMenuValue p_menu, boolean p_static_text, int64_t p_value_multiplier);


    void setName(StatsValue p_name);

    StatsValue getName();

    void setActor(RE::ActorValue p_actor);

    RE::ActorValue getActor();

    void setValue(std::string p_value);

    std::string getValue();

    void setDisplayName(std::string p_display_name);

    std::string getDisplayName();

    void setEnding(std::string p_ending);

    std::string getEnding();

    void setShow(boolean p_show);

    boolean getShow();

    void setGuiText(std::string p_gui_text);

    std::string getGuiText();

    void setStaticText(boolean p_static_text);

    boolean getStaticText();

    void setMenu(StatsMenuValue p_menu);

    StatsMenuValue getMenu();

    void setValueMultiplier(int64_t p_value_multiplier);

    int64_t getValueMultiplier();

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
    boolean show;
    std::string guiText;
    boolean staticText = false;
    StatsMenuValue menu = StatsMenuValue::mNone;
    int64_t valueMultiplier = 1;

    void buildText();

    void logItem();
};