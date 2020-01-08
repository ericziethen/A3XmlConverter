#pragma once

#include <string>

void ConvertStringToUtf8Unicode (std::string&);
void ConvertUtf8ToLocalCharSet (std::string&);
wchar_t *CodePageToUnicode(int, const char*);
char *UnicodeToCodePage(int, const wchar_t*);

