#pragma once

class FactionItem {
public:
    FactionItem(FactionValue p_name, std::string p_display_name, boolean p_show, FactionMenuValue p_menu);

    FactionItem(FactionValue p_name, std::string p_display_name, boolean p_show, FactionMenuValue p_menu,
        boolean p_display_is_value);

    void setName(FactionValue p_name);

    FactionValue getName();

    void setValue(std::string p_value);

    std::string getValue();

    void setDisplayName(std::string p_display_name);

    std::string getDisplayName();

    void setShow(boolean p_show);

    boolean getShow();

    void setGuiText(std::string p_gui_text);

    std::string getGuiText();

    void setMenu(FactionMenuValue p_menu);

    FactionMenuValue getMenu();

    void setDisplayIsValue(boolean p_display_is_value);

    boolean getDisplayIsValue();


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
    boolean show;
    std::string guiText;
    FactionMenuValue menu = FactionMenuValue::mNone;
    boolean displayIsValue = false;

    void buildText();

    void logItem();
};