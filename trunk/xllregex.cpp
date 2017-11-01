// xllregex.cpp - regular expressions using <regex>
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xllregex.h"

#ifndef CATEGORY_FORMAT
#define CATEGORY_FORMAT _T("Regex")
#endif

using namespace std;
using namespace xll;

/*
#ifdef _DEBUG
static AddInX xai_regex(
	ArgsX(CATEGORY)
	.Documentation(xml::Conceptual(_T("Regular Expressions"))
		.section(_T("Overview"), xml::element()
			.content(_T("This add-in does three things: detect exact regular expresion matches ("))
			.content(_T("REGEX.MATCH"))
			.content(_T("), replace text that matches a pattern with new text ("))
			.content(_T("REGEX.REPLACE"))
			.content(_T("), and breaks up text based on regular expression patterns ("))
			.content(_T("REGEX.SEARCH"))
			.content(_T(")."))
		)
		,
		xml::element()
		.content(
			xml::externalLink(_T("Regular Expressions"), _T("http://msdn.microsoft.com/en-us/library/bb982727.aspx"))
		)
		.content(xml::xlink(_T("REGEX.MATCH")))
		.content(xml::xlink(_T("REGEX.REPLACE")))
		.content(xml::xlink(_T("REGEX.SEARCH")))
	)
);
#endif // _DEBUG
*/
/*
static AddInX xai_regex_format(
	ArgsX(CATEGORY_FORMAT)
	.Documentation(xml::element()
		.content(xml::element(_T("para"))
			.content(_T("Format strings are used by <codeInline>REGEX.MATCH</codeInline>, "))
			.content(_T("<codeInline>REGEX.REPLACE</codeInline>, and "))
			.content(_T("<codeInline>REGEX.SEARCH</codeInline> to control the behavior of regular expression patterns. "))
		)
		.content(xml::element(_T("para"))
			.content(_T("There are two kinds of format strings: sed and default. "))
			.content(_T("Sed format strings use only the characters \\ and &amp; as special characters. "))
			.content(_T("The string \\<replaceable>n</replaceable>, where <replaceable>n</replaceable> "))
			.content(_T("is a digit, expands to the <replaceable>n</replaceable>-th sub-expression, while "))
			.content(_T("&amp; expands to the entire match. This is equivalent to \\0 in the default syntax. "))
		)
		,
		xml::element()
		.content(xml::xlink(_T("REGEX.MATCH")))
		.content(xml::xlink(_T("REGEX.REPLACE")))
		.content(xml::xlink(_T("REGEX.SEARCH")))
	)
);
*/

// format
XLL_ENUM_DOCX(regex_constants::format_default, 
	REGEX_FORMAT_DEFAULT, CATEGORY_FORMAT, _T("Use ECMAScript format rules."),
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::format_first_only, 
	REGEX_FORMAT_FIRST_ONLY, CATEGORY_FORMAT, _T("Do not search for matches after the first one."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::format_no_copy, 
	REGEX_FORMAT_NO_COPY, CATEGORY_FORMAT, _T("Do not copy text that does not match the regular expression."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::format_sed, 
	REGEX_FORMAT_SED, CATEGORY_FORMAT, _T("Use sed format rules."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));

// match
XLL_ENUM_DOCX(regex_constants::match_any, 
	REGEX_MATCH_ANY, CATEGORY_FORMAT, _T("If more than one match is possible any match is acceptable."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_continuous, 
	REGEX_MATCH_CONTINUOUS, CATEGORY_FORMAT, _T("Do not search for matches other than at the beginning of the target sequence."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_default, 
	REGEX_MATCH_DEFAULT, CATEGORY_FORMAT, _T("Use default matching rules."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_not_bol, 
	REGEX_MATCH_NOT_BOL, CATEGORY_FORMAT, _T("Do not treat the first position in the target sequence as the beginning of a line."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_not_bow, 
	REGEX_MATCH_NOT_BOW, CATEGORY_FORMAT, _T("Do not treat the first position in the target sequence as the beginning of a word."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_not_eol, 
	REGEX_MATCH_NOT_EOL, CATEGORY_FORMAT, _T("Do not treat the past-the-end position in the target sequence as the end of a line."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_not_eow, 
	REGEX_MATCH_NOT_EOW, CATEGORY_FORMAT, _T("Do not treat the past-the-end position in the target sequence as the end of a word."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_not_null, 
	REGEX_MATCH_NOT_NULL, CATEGORY_FORMAT, _T("Do not treat an empty subsequence as a match."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));
XLL_ENUM_DOCX(regex_constants::match_prev_avail, 
	REGEX_MATCH_PREV_AVAIL, CATEGORY_FORMAT, _T("First is a valid iterator; ignore match_not_bol and match_not_bow if set."), 
	_T("The type is a bitmask type that describes options to be used when matching a text sequence against a regular expression and format flags to be used when replacing text. Options can be combined with +."));

#ifdef _DEBUG

void xll_test_unellipsis()
{
	ensure (unellipsis(_T("abc")) ==  _T("abc"));
	ensure (unellipsis(_T("a\x85") _T("c")) ==  _T("a...c"));
	ensure (unellipsis(_T("a\x85") _T("c\x85")) ==  _T("a...c..."));
}

int xll_test_regex(void)
{
	try {
		xll_test_unellipsis();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return FALSE;
	}

	return TRUE;
}
static Auto<OpenAfterX> xao_test_regex(xll_test_regex);

#endif // _DEBUG