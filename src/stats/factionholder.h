#pragma once

class FactionItem {
public:
    FactionItem(FactionValue p_name, std::string p_display_name, bool p_show, FactionMenuValue p_menu) :
        name(p_name), displayName(p_display_name), show(p_show), menu(p_menu), value(""), guiText(""),
        displayIsValue(false) {
        this->logItem();
    }

    FactionItem(FactionValue p_name, std::string p_display_name, bool p_show, FactionMenuValue p_menu,
        bool p_display_is_value) :
        name(p_name),
        displayName(p_display_name), show(p_show), menu(p_menu), value(""), guiText(""),
        displayIsValue(p_display_is_value) {
        this->logItem();
    }

    FactionValue getName() { return name; }

    void setValue(std::string p_value) {
        if (!p_value.empty()) {
            value = p_value;
            logger::trace("set Value {} for name {} display {}"sv, p_value, name, displayName);
            buildText();
        }
    }

    std::string getValue() { return value; }

    std::string getDisplayName() { return displayName; }

    bool getShow() { return show; }

    std::string getGuiText() { return guiText; }

    FactionMenuValue getMenu() { return menu; }

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

    void buildText() { guiText = buildDisplayString(value, displayName, "", show, displayIsValue); }

    void logItem() {
        logger::trace("name {}, value {}, displayname ({}), show {}, guiText ({}), menu {}, VID {}"sv, name, value,
            displayName, show, guiText, menu, displayIsValue);
    }
};
