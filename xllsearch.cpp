// xllsearch.cpp - regex_search
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xllregex.h"

using namespace std;
using namespace xll;

static AddInX xai_regex_search(
	FunctionX(XLL_LPOPERX, _T("?xll_regex_search"), _T("REGEX.SEARCH"))
	.Arg(XLL_CSTRINGX, _T("Subject"), _T("is the text to be searched"),
		_T("The quick brown fox."))
	.Arg(XLL_CSTRINGX, _T("Pattern"), _T("is the regular expression"),
		_T("=IF(RAND()<.5, \"q\", \"b\")&\"\\S+\""))
	.Arg(XLL_LONGX, _T("?Flags"), _T("are optional flags from REGEX_MATCH_* describing the type of match to perform "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a one column array of all submatches from Subject that match Pattern."))
	.Documentation(
		_T("This function calls <codeInline>regex_search</codeInline> from the C++ standard library &lt;regex&gt;. ")
		_T("If there are no submatches it returns #N/A.")
/*		,
		xml::element()
		.content(xml::xlink(_T("REGEX.REPLACE")))
		.content(xml::xlink(_T("REGEX.MATCH")))
*/	)
);
LPOPERX WINAPI
xll_regex_search(xcstr subject, xcstr pattern, regex_constants::match_flag_type flags)
{
#pragma XLLEXPORT 
	static OPERX oResult;

	try {
		UDP_SEND;

		match_results<traits<XLOPERX>::xcstr> mr;

		if (regex_search(subject, mr, basic_regex<traits<XLOPERX>::xchar>(unellipsis(pattern)), flags)) {
			oResult.resize(static_cast<xword>(mr.size()), 1);
			for (xword i = 0; i < oResult.size(); ++i) {
				oResult[i] = mr[i].str();
			}
		}
		else {
			oResult = OPERX(xlerr::NA);
		}
	}
	catch (const exception& ex) {
		XLL_ERROR(ex.what());

		oResult = OPERX(xlerr::NA);
	}

	return &oResult;
}

XLL_TEST_BEGIN(search)

	OPERX o;
//	xcstr cmd{_T("XLL.SEARCH(\"\\bsub[^ ]\", \"a yellow submarine\")")};
	o = *xll_regex_search(_T("a yellow submarine"), _T("\\b(sub)([^ ]*)"), regex_constants::match_default);
	ensure (o.size() == 3);
	ensure (o[0] == _T("submarine"));
	ensure (o[1] == _T("sub"));
	ensure (o[2] == _T("marine"));

XLL_TEST_END(search)