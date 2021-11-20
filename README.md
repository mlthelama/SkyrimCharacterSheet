# ShowStats

## Nexus Mods
* [ShowStats](https://www.nexusmods.com/skyrimspecialedition/mods/56069/)

## End User Dependencies
* [SKSE64](https://skse.silverlock.org/)
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

## Build Dependencies
* [AutoTOML](https://github.com/Ryan-rsm-McKenzie/AutoTOML)
* [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE)
* [spdlog](https://github.com/gabime/spdlog)


## Building
```
git clone https://github.com/mlthelama/ShowStats.git
cd ShowStats

git submodule update --init --recursive
cmake -B build -S .
```