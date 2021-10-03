#pragma once
#include "stats/statholder.h"

class Filler
{
public:
	static Filler* GetSingleton();

	void PrintStatsVector(vector<StatItem>& p_vec);

	vector<StatItem> getData();

	vector<StatItem> statList;

	Filler() = default;
	Filler(const Filler&) = delete;
	Filler(Filler&&) = delete;

	~Filler() = default;

	Filler& operator=(const Filler&) = delete;
	Filler& operator=(Filler&&) = delete;

private:
	constants::MenuValue getMenu(int64_t p_menu_id);

	int64_t getMultiplier(int64_t p_mp);
};