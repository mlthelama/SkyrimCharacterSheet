import shutil
import os
import argparse
import zipfile
from os.path import basename

def copy_files(a_args, a_out):
    main = "main"
    skse_dir = os.path.join(a_out, main, "SKSE/Plugins/")
    #translation_dir = os.path.join(a_out, main, "Interface/Translations/")
    #script_dir = os.path.join(a_out, main, "Scripts/")
    main_dir = os.path.join(a_out, main)
    
    gui = "gui"
    gui_standard = os.path.join(a_out, gui, "standard/")
    gui_paper = os.path.join(a_out, gui, "paper/")
    gui_paper_light = os.path.join(a_out, gui, "paper_light/")

    os.makedirs(skse_dir + '/',exist_ok=True)
    shutil.copy2(os.path.join(a_args.src_dir, "ShowStats.toml"), os.path.join(skse_dir, "ShowStats.toml"))
    shutil.copy2(a_args.dll, os.path.join(skse_dir, os.path.basename(a_args.dll)))
 
    #os.makedirs(translation_dir + '/',exist_ok=True)
    #shutil.copy2(os.path.join(a_args.src_dir, "interface", "Translations", "ShowStats_english.txt"), os.path.join(translation_dir, "ShowStats_english.txt"))

    #os.makedirs(main_dir + '/',exist_ok=True)
    #shutil.copy2(os.path.join(a_args.src_dir, "mcm", "ShowStats.esp"), os.path.join(a_out, main))

    #os.makedirs(script_dir + '/',exist_ok=True)
    #shutil.copy2(os.path.join(a_args.src_dir, "mcm", "scripts", "ShowStats.pex"), os.path.join(script_dir, "ShowStats.pex"))
    #shutil.copy2(os.path.join(a_args.src_dir, "mcm", "scripts", "ShowStats_MCM.pex"), os.path.join(script_dir, "ShowStats_MCM.pex"))

    os.makedirs(gui_standard + '/',exist_ok=True)
    shutil.copy2(os.path.join(a_args.src_dir, "swf", "standard", "ShowStats.swf"), os.path.join(gui_standard, "ShowStats.swf"))
    shutil.copy2(os.path.join(a_args.src_dir, "swf", "standard", "ShowFactions.swf"), os.path.join(gui_standard, "ShowFactions.swf"))

    os.makedirs(gui_paper + '/',exist_ok=True)
    shutil.copy2(os.path.join(a_args.src_dir, "swf", "paper", "ShowStats.swf"), os.path.join(gui_paper, "ShowStats.swf"))
    shutil.copy2(os.path.join(a_args.src_dir, "swf", "paper", "ShowFactions.swf"), os.path.join(gui_paper, "ShowFactions.swf"))    

    os.makedirs(gui_paper_light + '/',exist_ok=True)
    shutil.copy2(os.path.join(a_args.src_dir, "swf", "paper_light", "ShowStats.swf"), os.path.join(gui_paper_light, "ShowStats.swf"))
    shutil.copy2(os.path.join(a_args.src_dir, "swf", "paper_light", "ShowFactions.swf"), os.path.join(gui_paper_light, "ShowFactions.swf"))

    

def make_rel_archive(a_args, a_out):
    #os.chdir(a_out)
    #archive = zipfile.ZipFile(a_args.name + ".zip", "w", zipfile.ZIP_DEFLATED)

    shutil.make_archive(a_args.name, "zip", a_out)
    
    #for root, dirs, files in os.walk(os.getcwd()):
    #    for file in files:
    #        archive.write(os.path.join(root, file))

def parse_arguments():
    parser = argparse.ArgumentParser(description="archive build artifacts for distribution")
    parser.add_argument("--name", type=str, help="the project name", required=True)
    parser.add_argument("--dll", type=str, help="the full dll path", required=True)
    parser.add_argument("--src-dir", type=str, help="the project root source directory", required=True)
    return parser.parse_args()
    
    
def main():
    out = "ShowStats"

    try:
        os.mkdir(out)
    except FileExistsError:
        pass
    #
    
    args = parse_arguments()
    copy_files(args, out)
    make_rel_archive(args, out)

if __name__ == "__main__":
    main()