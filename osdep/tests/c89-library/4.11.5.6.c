/* $Id$ */

#include <assert.h>
#include <string.h>

int main(void) {
	/*
	 * S4.11.5.6p2 "The strspn function returns the length of the segment."
	 */
	assert(strspn("", "") == 0);
	assert(strspn("abc", "") == 0);
	assert(strspn("", "abc") == 0);
	assert(strspn("abcdef", "a") == 1);
	assert(strspn("abcdef", "aa") == 1);
	assert(strspn("abcdef", "ba") == 2);
	assert(strspn("abcdef", "bb") == 0);
	assert(strspn("abcdef", "xyz") == 0);
	assert(strspn("abcdef", "aaa") == 1);
	assert(strspn("abcdef", "aba") == 2);
	assert(strspn("abcdef", "bab") == 2);
	assert(strspn("abcdef", "abc") == 3);
	assert(strspn("abcdef", "cba") == 3);
	assert(strspn("abcdef", "def") == 0);
	assert(strspn("abcdef", "defcba") == 6);
	assert(strspn("abcdef", "cbadef") == 6);

	return 0;
}

