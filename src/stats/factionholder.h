#pragma once

class FactionItem {
public:
    FactionItem(FactionValue p_name, std::string p_display_name, bool p_show, FactionMenuValue p_menu) {
        this->setName(p_name);
        this->setDisplayName(p_display_name);
        this->setShow(p_show);
        this->setMenu(p_menu);
        this->setDisplayIsValue(false);


        this->value.clear();
        this->guiText.clear();

        this->logItem();
    }

    FactionItem(FactionValue p_name, std::string p_display_name, bool p_show, FactionMenuValue p_menu,
        bool p_display_is_value) {
        this->setName(p_name);
        this->setDisplayName(p_display_name);
        this->setShow(p_show);
        this->setMenu(p_menu);
        this->setDisplayIsValue(p_display_is_value);


        this->value.clear();
        this->guiText.clear();

        this->logItem();
    }

    void setName(FactionValue p_name) { name = p_name; }

    FactionValue getName() { return name; }

    void setValue(std::string p_value) {
        value = p_value;
        logger::trace("set Value {} for name {} display {}"sv, p_value, name, displayName);
        buildText();
    }

    std::string getValue() { return value; }

    void setDisplayName(std::string p_display_name) { displayName = p_display_name; }

    std::string getDisplayName() { return displayName; }

    void setShow(bool p_show) { show = p_show; }

    bool getShow() { return show; }

    void setGuiText(std::string p_gui_text) { guiText = p_gui_text; }

    std::string getGuiText() { return guiText; }

    void setMenu(FactionMenuValue p_menu) { menu = p_menu; }

    FactionMenuValue getMenu() { return menu; }

    void setDisplayIsValue(bool p_display_is_value) { displayIsValue = p_display_is_value; }

    bool getDisplayIsValue() { return displayIsValue; }


    FactionItem() = delete;
    FactionItem(const FactionItem&) = default;
    FactionItem(FactionItem&&) = delete;

    ~FactionItem() = default;

    FactionItem& operator=(const FactionItem&) = default;
    FactionItem& operator=(FactionItem&&) = delete;

private:
    FactionValue name;
    std::string value;
    std::string displayName;
    bool show;
    std::string guiText;
    FactionMenuValue menu = FactionMenuValue::mNone;
    bool displayIsValue = false;

    void buildText() { guiText = buildDisplayString(value, displayName, "", show, false, displayIsValue); }

    void logItem() {
        logger::trace("name {}, value {}, displayname ({}), show {}, guiText ({}), menu {}, VID {}"sv, name, value,
            displayName, show, guiText, menu, displayIsValue);
    }
};
