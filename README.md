# Skyrim Character Sheet
![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=for-the-badge&logo=windows)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/mlthelama/SkyrimCharacterSheet?style=for-the-badge&include_prereleases)
![GitHub](https://img.shields.io/github/license/mlthelama/SkyrimCharacterSheet?style=for-the-badge)
![GitHub top language](https://img.shields.io/github/languages/top/mlthelama/SkyrimCharacterSheet?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/mlthelama/SkyrimCharacterSheet?style=for-the-badge)
![GitHub last commit](https://img.shields.io/github/last-commit/mlthelama/SkyrimCharacterSheet?style=for-the-badge)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/mlthelama/SkyrimCharacterSheet/main.yml?style=for-the-badge)

## Nexus Mods
* [Skyrim Character Sheet](https://www.nexusmods.com/skyrimspecialedition/mods/56069/)

## End User Dependencies
* [SKSE64](https://skse.silverlock.org/)
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

## Build Dependencies
* [CommonLibSSE NG](https://github.com/mlthelama/CommonLibSSE/tree/ng)
  - currently a [fork from](https://github.com/alandtse/CommonLibVR/tree/ng) with minor changes
  - added as [submodule](extern/CommonLibSSE-NG) 
* [spdlog](https://github.com/gabime/spdlog)
* [nlohmann-json](https://github.com/nlohmann/json)
* [tomlplusplus](https://github.com/marzer/tomlplusplus)
* [magic-enum](https://github.com/Neargye/magic_enum)
* [vcpkg](https://github.com/microsoft/vcpkg) 
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
  - on hash `93895b28ea7bc8cda10f156c5d336f3fc070f8b1`
* [cmake](https://cmake.org) 
  - installed dir needs to be added to the `PATH` environment variable
  - Version `3.25`
* [clib-util](https://github.com/powerof3/CLibUtil)
  - added as vcpkg [port](cmake/ports/clib-util)
* [unordered-dense](https://github.com/martinus/unordered_dense)
  - added as vcpkg [port](cmake/ports/unordered-dense)

## Release Dependencies
* [hint_button_menu](https://github.com/mlthelama/hint_button_menu)
  - needed [file](extern/hint_button_menu/bin/hint_button_menu.swf)
* [skyui](https://github.com/mlthelama/skyui)
  - needed [file](extern/skyui/swf/icons_item_psychosteve_merged.swf)

## Building
```
git clone https://github.com/mlthelama/SkyrimCharacterSheet.git
cd SkyrimCharacterSheet

cmake --preset vs2022-windows
cmake --build --preset vs2022-windows --config Release
```

## Manual Release
```
cd SkyrimCharacterSheet

./scripts/run.sh 
or
.\scripts\run.sh
```
