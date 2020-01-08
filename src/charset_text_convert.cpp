#include "charset_text_convert.h"

#include "windows.h"

#define UTF8_UNICODE_CODE 65001

void ConvertStringToUtf8Unicode (std::string& InputString)
{
	// Get current encoding from system
	wchar_t *wText = CodePageToUnicode(GetACP(), InputString.c_str());

	// convert to utf
	char *utf8Text = UnicodeToCodePage(UTF8_UNICODE_CODE,wText);

	InputString = utf8Text;
} // ConvertStringToUtf8Unicode

void ConvertUtf8ToLocalCharSet (std::string& InputString)
{
	// Get unicode Encoding
	wchar_t *wText2 = CodePageToUnicode(UTF8_UNICODE_CODE, InputString.c_str());

	// Convert to Local char set
	char *localCharText = UnicodeToCodePage(GetACP(), wText2);

	InputString = localCharText;
} // ConvertUtf8ToLocalCharSet

// 65001 is utf-8.
wchar_t *CodePageToUnicode(int codePage, const char *src)
{
	if (!src) return 0;
	int srcLen = strlen(src);
	if (!srcLen)
	{
		wchar_t *w = new wchar_t[1];
		w[0] = 0;
		return w;
	}

	int requiredSize = MultiByteToWideChar(codePage,
		0,
		src,srcLen,0,0);

	if (!requiredSize)
	{
		return 0;
	}

	wchar_t *w = new wchar_t[requiredSize+1];
	w[requiredSize] = 0;

	int retval = MultiByteToWideChar(codePage,
		0,
		src,srcLen,w,requiredSize);
	if (!retval)
	{
		delete [] w;
		return 0;
	}

	return w;
} // CodePageToUnicode

char *UnicodeToCodePage(int codePage, const wchar_t *src)
{
	if (!src) return 0;
	int srcLen = wcslen(src);
	if (!srcLen)
	{
		char *x = new char[1];
		x[0] = '\0';
		return x;
	}

	int requiredSize = WideCharToMultiByte(codePage,
		0,
		src,srcLen,0,0,0,0);

	if (!requiredSize)
	{
		return 0;
	}

	char *x = new char[requiredSize+1];
	x[requiredSize] = 0;

	int retval = WideCharToMultiByte(codePage,
		0,
		src,srcLen,x,requiredSize,0,0);
	if (!retval)
	{
		delete [] x;
		return 0;
	}

	return x;
} // UnicodeToCodePage
