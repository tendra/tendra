#include <assert.h>

int main(void) {
	/*
	 * S3.2.2.2p1 "If an expression of any other type occurs in a context
	 * where a void expression is required, its value or designator is
	 * discarded."
	 */
	5;

	/*
	 * S3.2.2.2p1 "A void expression is evaluated for its side effects."
	 */
	{
		int i;
		i = 0;
		(void) i++;
		assert(i == 1);
	}

	return 0;
}

