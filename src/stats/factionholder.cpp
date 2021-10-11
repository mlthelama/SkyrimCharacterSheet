#pragma once
#include "stats/factionholder.h"
#include "utils.h"

FactionItem::FactionItem(FactionValue p_name, std::string p_display_name, boolean p_show, FactionMenuValue p_menu) {
    this->setName(p_name);
    this->setDisplayName(p_display_name);
    this->setShow(p_show);
    this->setMenu(p_menu);
    this->setDisplayIsValue(false);


    this->value.clear();
    this->guiText.clear();

    this->logItem();
}

FactionItem::FactionItem(FactionValue p_name, std::string p_display_name, boolean p_show, FactionMenuValue p_menu,
    boolean p_display_is_value) {
    this->setName(p_name);
    this->setDisplayName(p_display_name);
    this->setShow(p_show);
    this->setMenu(p_menu);
    this->setDisplayIsValue(p_display_is_value);


    this->value.clear();
    this->guiText.clear();

    this->logItem();
}

void FactionItem::setName(FactionValue p_name) { name = p_name; }

FactionValue FactionItem::getName() { return name; }

void FactionItem::setValue(std::string p_value) {
    value = p_value;
    logger::trace("set Value {} for name {} display {}"sv, p_value, name, displayName);
    buildText();
}

std::string FactionItem::getValue() { return value; }

void FactionItem::setDisplayName(std::string p_display_name) { displayName = p_display_name; }

std::string FactionItem::getDisplayName() { return displayName; }

void FactionItem::setShow(boolean p_show) { show = p_show; }

boolean FactionItem::getShow() { return show; }

void FactionItem::setGuiText(std::string p_gui_text) { guiText = p_gui_text; }

std::string FactionItem::getGuiText() { return guiText; }

void FactionItem::setMenu(FactionMenuValue p_menu) { menu = p_menu; }

FactionMenuValue FactionItem::getMenu() { return menu; }

void FactionItem::setDisplayIsValue(boolean p_display_is_value) { displayIsValue = p_display_is_value; }

boolean FactionItem::getDisplayIsValue() { return displayIsValue; }

void FactionItem::buildText() { guiText = buildDisplayString(value, displayName, "", show, false, displayIsValue); }

void FactionItem::logItem() {
    logger::trace("name {}, value {}, displayname ({}), show {}, guiText ({}), menu {}, VID {}"sv, name, value,
        displayName, show, guiText, menu, displayIsValue);
}