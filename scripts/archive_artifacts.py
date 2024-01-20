import argparse
import os
import zipfile
from pathlib import Path

def make_rel_archive(a_args):
    archive = zipfile.ZipFile(a_args.name + ".zip", "w", zipfile.ZIP_DEFLATED)

    # english is already existing, those are just needed to copy the english one
    languages = ["czech", "french", "german", "italian", "japanese", "polish", "russian", "spanish"]

    os.chdir('../')
    v_pwd: str = os.getcwd()
    if (a_args.dir):
        v_pwd: str = os.path.join(os.getcwd(), a_args.dir)

    resource_extensions: list[str] = ["*.json"]
    v_path: str = os.path.join(v_pwd, "config")
    for extension in resource_extensions:
        for path in Path(v_path).rglob(extension):
            archive.write(path, os.path.join("SKSE/Plugins/SkyrimCharacterSheet/", path.relative_to(v_path)))

    archive.write(os.path.join(v_pwd, a_args.dll), "SKSE/Plugins/{}".format(os.path.basename(a_args.dll)))
    archive.write(os.path.join(v_pwd, a_args.pdb), "SKSE/Plugins/{}".format(os.path.basename(a_args.pdb)))
    archive.write(os.path.join(v_pwd, "swf", "standard", "ShowStats.swf"), "Interface/ShowStats.swf")
    archive.write(os.path.join(v_pwd, "swf", "standard", "ShowFactions.swf"), "Interface/ShowFactions.swf")
    archive.write(os.path.join(v_pwd, "swf", "standard", "ShowStatsInventory.swf"),
                  "Interface/ShowStatsInventory.swf")
    archive.write(os.path.join(v_pwd, "swf", "Translations", "SkyrimCharacterSheet_english.txt"),
                  "Interface/Translations/SkyrimCharacterSheet_english.txt")

    for lang in languages:
        archive.write(os.path.join(v_pwd, "swf", "Translations", "SkyrimCharacterSheet_english.txt"),
                      "Interface/Translations/SkyrimCharacterSheet_" + lang + ".txt")

    archive.write(os.path.join(v_pwd, "extern", "skyui", "swf", "icons_item_psychosteve_merged.swf"), "Interface/skyui/icons_item_psychosteve_merged.swf")
    archive.write(os.path.join(v_pwd, "extern", "hint_button_menu", "bin", "hint_button_menu.swf"), "Interface/ShowTweenHintMenu.swf")


def parse_arguments():
    parser = argparse.ArgumentParser(description="archive build artifacts for distribution")
    parser.add_argument("--dll", type=str, help="the full dll path", required=True)
    parser.add_argument("--name", type=str, help="the project name", required=True)
    parser.add_argument("--pdb", type=str, help="the full pdb path", required=True)
    parser.add_argument("--dir", type=str, help="additonal", required=False)
    return parser.parse_args()


def main():
    out = "artifacts"
    try:
        os.mkdir(out)
    except FileExistsError:
        pass
    os.chdir(out)

    args = parse_arguments()
    make_rel_archive(args)


if __name__ == "__main__":
    main()
