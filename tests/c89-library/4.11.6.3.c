#include <assert.h>
#include <string.h>

int main(void) {
	/*
	 * S4.11.6.3p2 "The strlen function returns the number of characters
	 * that precede the terminating null character."
	 */
	assert(strlen("") == 0);
	assert(strlen("x") == 1);
	assert(strlen("abc") == 3);
	assert(strlen("abc\0") == 3);
	assert(strlen("abc\0xyz") == 3);

	return 0;
}

