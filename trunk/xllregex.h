// xllregex.h - <regex> library
#pragma once
#include <string>
#include <regex>
#define EXCEL12
#include "xll/xll.h"
#include "xll/udp.h"

#ifndef CATEGORY
#define CATEGORY _T("Regex")
#endif

typedef xll::traits<XLOPERX>::xchar xchar;
typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xstring xstring;
typedef xll::traits<XLOPERX>::xword xword;

// Excel converts "..." into this character.
inline xstring
unellipsis(xcstr str)
{
	static std::basic_regex<xchar> ell(_T("\x85"));
	static xstring ddd(_T("..."));

	return regex_replace(str, ell, ddd);
}