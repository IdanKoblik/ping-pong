#include "headers/strutils.h"

void safeStrCopy(char* dest, const char* src, size_t destSize, size_t* actualSize) {
    size_t len = strnlen(src, destSize - 1);
    strncpy(dest, src, len);
    dest[len] = '\0';  // Null-terminate the string
    *actualSize = len;
}