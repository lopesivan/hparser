#ifndef VERSION_CPP
#define VERSION_CPP

#include "version.hpp"

#define STR1(str) #str
#define STR2(str) STR1(str)

#define HPARSER_VERSION STR2(HPARSER_MAJ) "." \
			STR2(HPARSER_MIN) "." \
			STR2(HPARSER_UPDT)

const char HPVersion[] = HPARSER_VERSION;

extern const unsigned int HPMajor  = HPARSER_MAJ;
extern const unsigned int HPMinor  = HPARSER_MIN;
extern const unsigned int HPUpdate = HPARSER_UPDT;

#undef STR1
#undef STR2
#undef HPARSER_VERSION

#endif
