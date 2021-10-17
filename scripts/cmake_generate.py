import os

SOURCE_TYPES = (
    ".c",
    ".cpp",
    ".cxx",
    ".h",
    ".hpp",
    ".hxx",
)

def make_cmake(a_directories, p_name, p_first):
    tmp = []
    for directory in a_directories:
        for root, dirs, files in os.walk(directory):
            for file in files:
                if file.endswith(SOURCE_TYPES):
                    path = os.path.join(root, file)
                    tmp.append(os.path.normpath(path))

    sources = []
    for file in tmp:
        sources.append(file.replace("\\", "/"))
    sources.sort()

    out = open(os.path.join("cmake", p_name), "w")
    out.write(p_first)
    for source in sources:
        out.write("\t{}\n".format(source))
    out.write(")\n")

def main():
    cur = os.path.dirname(os.path.realpath(__file__))
    os.chdir(cur + "/..")
    make_cmake([ "src" ], "sourcelist.cmake", "set(sources ${sources}\n")
    #make_cmake([ "include" ], "headerlist.cmake", "set(headers ${headers}\n")

if __name__ == "__main__":
    main()
