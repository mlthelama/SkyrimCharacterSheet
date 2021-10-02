#pragma once
#include "stats/statholder.h"


StatItem::StatItem(constants::StatsValue p_name,
	RE::ActorValue p_actor,
	string p_display_name,
	string p_ending,
	boolean p_show
) {
	this->setName(p_name);
	this->setActor(p_actor);
	this->setDisplayName(p_display_name);
	this->setEnding(p_ending);
	this->setShow(p_show);
	this->setMenu(constants::MenuValue::mNone);
	this->setStaticText(false);

	this->value.clear();
	this->guiText.clear();

	this->logItem();
}

StatItem::StatItem(constants::StatsValue p_name,
	RE::ActorValue p_actor,
	string p_display_name,
	string p_ending,
	boolean p_show,
	constants::MenuValue p_menu
) { 
	this->setName(p_name);
	this->setActor(p_actor);
	this->setDisplayName(p_display_name);
	this->setEnding(p_ending);
	this->setShow(p_show);
	this->setMenu(p_menu);
	this->setStaticText(false);

	this->value.clear();
	this->guiText.clear();

	this->logItem();
};

StatItem::StatItem(constants::StatsValue p_name, 
	RE::ActorValue p_actor, 
	string p_display_name,	
	string p_ending, 
	boolean p_show, 
	constants::MenuValue p_menu,
	boolean p_static_text
) {
	this->setName(p_name);
	this->setActor(p_actor);
	this->setDisplayName(p_display_name);
	this->setEnding(p_ending);
	this->setShow(p_show);
	this->setMenu(p_menu);
	this->setStaticText(p_static_text);

	this->value.clear();
	this->guiText.clear();

	this->logItem();
};

StatItem::StatItem(constants::StatsValue p_name,
	RE::ActorValue p_actor,
	string p_display_name,
	string p_ending,
	boolean p_show,
	constants::MenuValue p_menu,
	int32_t p_value_multiplier
) {
	this->setName(p_name);
	this->setActor(p_actor);
	this->setDisplayName(p_display_name);
	this->setEnding(p_ending);
	this->setShow(p_show);
	this->setMenu(p_menu);
	this->setValueMultiplier(p_value_multiplier);

	this->setStaticText(false);

	this->value.clear();
	this->guiText.clear();

	this->logItem();
};

void StatItem::setName(constants::StatsValue p_name) { name = p_name; }

constants::StatsValue StatItem::getName() { return name; }

void StatItem::setActor(RE::ActorValue p_actor) { actor = p_actor; }

RE::ActorValue StatItem::getActor() { return actor; }

void StatItem::setValue(string p_value) {
	value = p_value;
	logger::trace("set Value {} for name {} display {}"sv, p_value, name, displayName);
	buildText();
}

string StatItem::getValue() { return value; }

void StatItem::setDisplayName(string p_display_name) { displayName = p_display_name; }

string StatItem::getDisplayName() { return displayName; }

void StatItem::setEnding(string p_ending) { ending = p_ending; }

string StatItem::getEnding() { return ending; }

void StatItem::setShow(boolean p_show) { show = p_show; }

boolean StatItem::getShow() { return show; }

void StatItem::setGuiText(string p_gui_text) { guiText = p_gui_text; }

string StatItem::getGuiText() { return guiText; }

void StatItem::setStaticText(boolean p_static_text) { staticText = p_static_text; }

boolean StatItem::getStaticText() { return staticText; }

void StatItem::setMenu(constants::MenuValue p_menu) { menu = p_menu; }

constants::MenuValue StatItem::getMenu() { return menu; }

void StatItem::setValueMultiplier(int32_t p_value_multiplier) { valueMultiplier = p_value_multiplier; }

int32_t StatItem::getValueMultiplier() { return valueMultiplier; }

void StatItem::buildText() {
	if (!value.empty() && !displayName.empty() && !show) {
		return;
	}

	guiText.clear();

	guiText = displayName;
	if (value.size() > 0) {
		guiText += ": ";
	}

	guiText += (staticText) ? value : constants::cutString(value);

	guiText += ending;
}

void StatItem::logItem() {
	logger::trace("name {}, actor {}, value {}, displayname ({}), ending {}, show {}, guiText ({}), ST {}, menu {}, VMP {}"sv,
		name,
		actor,
		value,
		displayName,
		ending,
		show,
		guiText,
		staticText,
		menu,
		valueMultiplier
	);
}