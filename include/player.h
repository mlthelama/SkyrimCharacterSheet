#pragma once

typedef std::map<std::string, std::string> ValueMap;

class Player
{
public:
	static Player* GetSingleton();
	//maybe add save/load

	ValueMap getValues();

private:
	ValueMap GatherValues();
	void PrintValues(ValueMap& p_map);



	using Lock = std::recursive_mutex;
	using Locker = std::lock_guard<Lock>;

	Player();
	Player(const Player&) = delete;
	Player(Player&&) = delete;
	~Player() = default;

	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	mutable Lock _lock;
};