/* $Id$ */

#include <assert.h>

/*
 * S4.1.5p1 "The following types and macros are defined in
 * the standard header <stddef.h>."
 */
#include <stddef.h>

int main(void) {
	/*
	 * S4.1.5p2 "ptrdiff_t which is the signed integral type ..."
	 */
	{
		ptrdiff_t t;
		t = -1;
		assert(t == -1);
	}

	/*
	 * S4.1.5p2 "... of the result * of subtracting two pointers;"
	 */
	{
		char c;
		char *a = &c, *b = &c;
		assert(sizeof (a - b) == sizeof (ptrdiff_t));
	}

	/*
	 * S4.1.5p3 "size_t which is the unsigned integral type ..."
	 */
	{
		size_t z;
		z = 1;
		assert(z == 1);
	}

	/*
	 * S4.1.5p3 "... of the result of the sizeof operator;"
	 */
	{
		int i;
		assert(sizeof sizeof i == sizeof (size_t));
	}

	/*
	 * S4.1.5p4 "wchar_t which is an integral type ..."
	 */
	{
		wchar_t c;
		c = 1;
		assert(c == 1);
	}

	/*
	 * S4.1.5p4 "... whose range of values can represent distinct
	 * codes for all members of the largest extended character set specified
	 * among the supported locales;"
	 */
	{
		wchar_t a[] = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
			'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'!', '"', '#', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':',
			';', '<', '=', '>', '?', '[', '\\', ']', '^', '_', '{', '|', '}', '~',
			' ', '\t', '\v', '\f' };
		int i, j;
		for (i = 0; i < sizeof a / sizeof *a; i++) {
			for (j = i + 1; j < sizeof a / sizeof *a; j++) {
				assert(a[i] != a[j]);
			}
		}
	}

	/*
	 * S4.1.5p4 "... the null character shall have the code value zero ..."
	 */
	assert('\0' == 0);

	/*
	 * UNTESTED: S4.1.5p4 "... and each member of the basic character set defined in
	 * $2.2.1 shall have a code value equal to its value when used as the
	 * lone character in an integer character constant."
	 */

	/*
	 * S4.1.5p5 "The macros are NULL which expands to an implementation-defined
	 * null pointer constant;"
	 */
	assert(NULL == 0);
	assert(NULL == (void *) 0);

	/*
	 * S4.1.5p6 "...and offsetof( type,  member-designator)
	 * which expands to an integral constant expression ..."
	 */
	{
		struct s { int m; };
		int a[offsetof(struct s, m)];
		enum { e = offsetof(struct s, m) };
		static int i = offsetof(struct s, m);
		switch (5) { case offsetof(struct s, m): ; }
	}

	/*
	 * S4.1.5p6 "... that has type size_t ..."
	 */
	{
		struct s { int m; };
		assert(sizeof offsetof(struct s, m) == sizeof (size_t));
	}

	/*
	 * S4.1.5p6 "... the value of which is the offset in bytes, to the structure member
	 * (designated by member-designator), from the beginning of its
	 * structure (designated by type)."
	 */
	{
		struct s { int m; };
		assert(offsetof(struct s, m) == 0);
	}

	return 0;
}

