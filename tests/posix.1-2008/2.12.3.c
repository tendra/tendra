#include <assert.h>
#include <string.h>

int main(void) {

	/*
	 * S2.12.3 "All function pointer types shall have the same
	 * representation as the type pointer to void."
	 */
	{
		void (*f)(void) = 0;
		void *p = 0;
		assert(sizeof f == sizeof p);
		assert(0 == memcmp(&f, &p, sizeof f));
	}

	/*
	 * "S2.12.3 "Conversion of a function pointer to void * shall not
	 * alter the representation."
	 */
	{
		int (*f)(void) = main;
		void *p = (void *) f;
		assert(sizeof f == sizeof p);
		assert(0 == memcmp(&f, &p, sizeof f));
	}

	/*
	 * S2.12.3 "A void * value resulting from such a conversion
	 * can be converted back to the original function pointer type,
	 * using an explicit cast, without loss of information."
	 */
	{
		int (*f)(void) = main;
		void *p = (void *) f;
		int (*g)(void) = (int (*)(void)) p;
		assert(0 == memcmp(&f, &g, sizeof f));
	}

	return 0;
}

