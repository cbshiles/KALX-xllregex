// xllmatch.cpp - regex_match
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xllregex.h"

using namespace std;
using namespace xll;

static AddInX xai_regex_match(
	FunctionX(XLL_BOOLX, _T("?xll_regex_match"), _T("REGEX.MATCH"))
	.Arg(XLL_CSTRINGX, _T("Subject"), _T("is the text to be matched"),
		_T("=INT(200*RAND())"))
	.Arg(XLL_CSTRINGX, _T("Pattern"), _T("is the regular expression"),
		_T("'\\d{2}"))
	.Arg(XLL_LONGX, _T("Flags"), _T("are optional flags from REGEX_MATCH_* describing the type of match to perform "),
		_T("=REGEX_MATCH_DEFAULT()"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns TRUE if Subject *exactly* matches Pattern and FALSE if not."))
	.Documentation(
		_T("This function calls <codeInline>regex_match</codeInline> from the C++ standard library &lt;regex&gt;. ")
/*		,
		xml::element()
		.content(xml::xlink(_T("REGEX.REPLACE")))
		.content(xml::xlink(_T("REGEX.SEARCH")))
*/	)
);
BOOL WINAPI
xll_regex_match(xcstr subject, xcstr pattern, regex_constants::match_flag_type flags)
{
#pragma XLLEXPORT 
	try {
		UDP_SEND;

		return regex_match(subject, basic_regex<xchar>(unellipsis(pattern)), flags);
	}
	catch (const exception& ex) {
		XLL_ERROR(ex.what());
	}

	return FALSE;
}
