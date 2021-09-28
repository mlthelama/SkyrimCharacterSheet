#ifndef version_included
#define version_included

#define version_string_maker(a_str) #a_str
#define string_maker(a_str) version_string_maker(a_str)

#define version_major 0
#define version_minor 0
#define verion_patch 0
#define version_beta 4

#define version_string string_maker(version_major) "." string_maker(version_minor) "." string_maker(verion_patch) "." string_maker(version_beta)

#endif	// !version_included