#pragma once
#include "constants.h"

class StatItem
{
public:
	StatItem(StatsValue p_name,
		RE::ActorValue p_actor,
		string p_display_name,
		string p_ending,
		boolean p_show
	);

	StatItem(StatsValue p_name,
		RE::ActorValue p_actor,
		string p_display_name,
		string p_ending,
		boolean p_show,
		MenuValue p_menu
	);

	StatItem(StatsValue p_name,
		RE::ActorValue p_actor,
		string p_display_name,
		string p_ending,
		boolean p_show,
		MenuValue p_menu,
		boolean p_static_text
	);

	StatItem(StatsValue p_name,
		RE::ActorValue p_actor,
		string p_display_name,
		string p_ending,
		boolean p_show,
		MenuValue p_menu,
		boolean p_static_text, 
		int64_t p_value_multiplier
	);


	void setName(StatsValue p_name);

	StatsValue getName();

	void setActor(RE::ActorValue p_actor);

	RE::ActorValue getActor();

	void setValue(string p_value);

	string getValue();

	void setDisplayName(string p_display_name);

	string getDisplayName();

	void setEnding(string p_ending);

	string getEnding();

	void setShow(boolean p_show);

	boolean getShow();

	void setGuiText(string p_gui_text);

	string getGuiText();

	void setStaticText(boolean p_static_text);

	boolean getStaticText();

	void setMenu(MenuValue p_menu);

	MenuValue getMenu();

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
	string value;
	string displayName;
	string ending;
	boolean show;
	string guiText;
	boolean staticText = false;
	MenuValue menu = MenuValue::mNone;
	int64_t valueMultiplier = 1;

	void buildText();

	void logItem();
};