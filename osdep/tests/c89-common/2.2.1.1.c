/* $Id: 3.2.2.2p1.c 2773 2012-06-06 04:21:57Z kate $ */

#include <assert.h>

int main(void) {
	/*
	 * S2.2.1.1p1 "All occurrences in a source file of the following sequences of
	 * three characters (called trigraph sequences) are replaced with the
	 * corresponding single character."
	 */
	{
		assert('??=' == '#');
		assert('??(' == '[');
		assert('??/\' == '\\');
		assert('??/t' == '\t');
		assert('??)' == ']');
		assert('??'' == '^');
		assert('??<' == '{');
		assert('??!' == '|');
		assert('??>' == '}');
		assert('??-' == '~');

		assert(*"??=" == '#');
		assert(*"??(" == '[');
		assert(*"??/\" == '\\');
		assert(*"??/t" == '\t');
		assert(*"??)" == ']');
		assert(*"??'" == '^');
		assert(*"??<" == '{');
		assert(*"??!" == '|');
		assert(*"??>" == '}');
		assert(*"??-" == '~');

??=define s(s) ??=s

		assert(*s(x) == 'x');
		assert(*s(??=) == '#');

#undef s

		assert(??-1U ??' 1U == 0U);
		assert(1U ??! 2U == 3U);
		assert("x"??(0] == 'x');
		assert("x"[0??) == 'x');

		??< assert(1); }
		{ assert(1); ??>

#define x "x" ??/
	"y"

		assert(x[0] == 'x');
		assert(x[1] == 'y');
		assert(x[2] == '\0');
#undef x

		assert(*"??/
" == '\0');
	}

	/*
	 * S2.2.1.1p2 "No other trigraph sequences exist. Each ? that does not
	 * begin one of the trigraphs listed above is not changed."
	 */
	{
		assert("???"[0] == '?');
		assert("???"[1] == '?');
		assert("???"[2] == '?');
		assert("???"[3] == '\0');
	}

	return 0;
}

