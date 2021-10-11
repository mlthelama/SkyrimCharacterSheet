#pragma once

class Thane {
public:
    static Thane* GetSingleton();

    std::string getThane(FactionValue p_stat);

    void getRegionThanes();

    Thane() = default;
    Thane(const Thane&) = delete;
    Thane(Thane&&) = delete;

    ~Thane() = default;

    Thane& operator=(const Thane&) = delete;
    Thane& operator=(Thane&&) = delete;

private:
    valueStringMap thaneList;

    void logMap();
};