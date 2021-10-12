#pragma once

class ShowHandler {
public:
    static ShowHandler* GetSingleton();
    //maybe add save/load

    void CloseWindow(ShowMenu p_menu);

    void SwapWindow(ShowMenu p_menu_open, ShowMenu p_menu_close);

    void CloseAllWindows();

    void HandleMainButtonPress();

    void HandleNextMenuButtonPress();

private:
    using Lock = std::recursive_mutex;
    using Locker = std::lock_guard<Lock>;

    void ShowWindow(ShowMenu p_menu);

    ShowHandler();
    ShowHandler(const ShowHandler&) = delete;
    ShowHandler(ShowHandler&&) = delete;
    ~ShowHandler() = default;

    ShowHandler& operator=(const ShowHandler&) = delete;
    ShowHandler& operator=(ShowHandler&&) = delete;

    mutable Lock _lock;
};