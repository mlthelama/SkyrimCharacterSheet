#pragma once
#include "constants.h"
#include "settings.h"

class StatItem
{
public:
	StatItem(constants::StatsValue p_name,
		RE::ActorValue p_actor,
		string p_display_name,
		string p_ending,
		boolean p_show
	);

	StatItem(constants::StatsValue p_name,
		RE::ActorValue p_actor,
		string p_display_name,
		string p_ending,
		boolean p_show,
		constants::MenuValue p_menu
	);

	StatItem(constants::StatsValue p_name,
		RE::ActorValue p_actor,
		string p_display_name,
		string p_ending,
		boolean p_show,
		constants::MenuValue p_menu,
		boolean p_static_text
	);

	void setName(constants::StatsValue p_name);

	constants::StatsValue getName();

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

	void setMenu(constants::MenuValue p_menu);

	constants::MenuValue getMenu();


	StatItem() = delete;
	StatItem(const StatItem&) = default;
	StatItem(StatItem&&) = delete;

	~StatItem() = default;

	StatItem& operator=(const StatItem&) = default;
	StatItem& operator=(StatItem&&) = delete;

private:
	constants::StatsValue name;
	RE::ActorValue actor;
	string value;
	string displayName;
	string ending;
	boolean show;
	string guiText;
	boolean staticText = false;
	constants::MenuValue menu = constants::MenuValue::mNone;

	void buildText();

	void logItem();
};