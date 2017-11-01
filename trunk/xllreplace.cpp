// xllreplace.cpp - regex_replace
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xllregex.h"

using namespace std;
using namespace xll;

static AddInX xav_regex_replace(
	FunctionX(XLL_CSTRINGX, _T("?xll_regex_replace"), _T("REGEX.REPLACE"))
	.Arg(XLL_CSTRINGX, _T("Subject"), _T("is the text to be searched"),
		_T("ABCabc"))
	.Arg(XLL_CSTRINGX, _T("Pattern"), _T("is the regular expression"),
		_T("=IF(RAND()<.5, \"a\", \"b\""))
	.Arg(XLL_CSTRINGX, _T("Replace"), _T("is the replacement text "),
		_T("=IF(RAND()<.5, \"y\", \"z\""))
	.Arg(XLL_LONGX, _T("?Flags"), _T("are optional flags from REGEX_MATCH_* describing the type of match to perform "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Replace text in Subject substrings matching Pattern."))
	.Documentation(
		_T("This function calls <codeInline>regex_replace</codeInline> from the C++ standard library &lt;regex&gt;. ")
/*		,
		xml::element()
		.content(xml::xlink(_T("REGEX.MATCH")))
		.content(xml::xlink(_T("REGEX.SEARCH")))
*/	)
);
xcstr WINAPI
xll_regex_replace(xcstr subject, xcstr pattern, xcstr replace, regex_constants::match_flag_type flags)
{
#pragma XLLEXPORT 
	static xstring result;

	try {
		UDP_SEND;

		basic_regex<xchar> re(unellipsis(pattern));

		result = regex_replace(subject, re, replace, flags);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
		
		return 0;
	}

	return result.c_str();
}
