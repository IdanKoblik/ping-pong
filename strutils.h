#include <string.h>

#ifndef MALWARE_STRUTILS_H
#define MALWARE_STRUTILS_H

void safeStrCopy(char* dest, const char* src, size_t destSize, size_t* actualSize);

#endif //MALWARE_STRUTILS_H
