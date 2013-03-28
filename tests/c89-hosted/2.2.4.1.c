/* $Id$ */

#include <assert.h>

int main(void) {
	/*
	 * S2.2.4.1 "The implementation shall be able to translate and execute
	 * at least one program that contains at least one instance of every
	 * one of the following limits:"
	 */

	/*
	 * "32767 bytes in an object (in a hosted environment only)"
	 */
	{
		char a[32767];

		assert(sizeof a == 32767);
	}

	/* UNTESTED: other limits (all of which must be simultaneously present) */

	return 0;
}

