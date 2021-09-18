#pragma once

class ShowHandler
{
public:
	static ShowHandler* GetSingleton();
	//maybe add save/load

	void ShowWindow();

private:
	using Lock = std::recursive_mutex;
	using Locker = std::lock_guard<Lock>;

	ShowHandler();
	ShowHandler(const ShowHandler&) = delete;
	ShowHandler(ShowHandler&&) = delete;
	~ShowHandler() = default;

	ShowHandler& operator=(const ShowHandler&) = delete;
	ShowHandler& operator=(ShowHandler&&) = delete;

	void Show();

	mutable Lock _lock;
};