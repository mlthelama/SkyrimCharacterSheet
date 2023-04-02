# Skyrim Character Sheet
![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=plastic&logo=windows)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/mlthelama/SkyrimCharacterSheet?style=plastic)
![GitHub](https://img.shields.io/github/license/mlthelama/SkyrimCharacterSheet?style=plastic)
![GitHub top language](https://img.shields.io/github/languages/top/mlthelama/SkyrimCharacterSheet?style=plastic)
![GitHub language count](https://img.shields.io/github/languages/count/mlthelama/SkyrimCharacterSheet?style=plastic)
![GitHub last commit](https://img.shields.io/github/last-commit/mlthelama/SkyrimCharacterSheet?style=plastic)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/mlthelama/SkyrimCharacterSheet/main.yml?style=plastic)

## Nexus Mods
* [Skyrim Character Sheet](https://www.nexusmods.com/skyrimspecialedition/mods/56069/)

## End User Dependencies
* [SKSE64](https://skse.silverlock.org/)
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
* [Scaleform Translation Plus Plus](https://www.nexusmods.com/skyrimspecialedition/mods/22603)
* [Icons for Skyrim Character Sheet](https://www.nexusmods.com/skyrimspecialedition/mods/71282)

## Build Dependencies
* [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG)
* [spdlog](https://github.com/gabime/spdlog)
* [simpleini](https://github.com/brofield/simpleini)
* [vcpkg](https://github.com/microsoft/vcpkg) 
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [cmake](https://cmake.org) 
  - installed dir needs to be added to the `PATH` environment variable

## Building
```
git clone https://github.com/mlthelama/SkyrimCharacterSheet.git
cd SkyrimCharacterSheet

cmake --preset vs2022-windows
cmake --build --preset vs2022-windows --config Release
```
