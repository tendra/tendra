/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include "../fmt.h"
#include "../error.h"


struct x {
	int a;
	int b;
	int c;
};

static void fmt_x(FILE *fp, void *p) {
	struct x *x = p;

	fprintf(fp, "%d/%d/%d", x->a, x->b, x->c);
}

int main(void) {
	struct x x1 = { 1, 2, 3 };
	struct x x2 = { 4, 5, 6 };
	long l = 123;
	unsigned long ul = 456;

	fmt_register('R', fmt_x);

	efprintf(stdout, "%ld %lu %% %d %R %R %s %.2s %.*s\n",
		l, ul, 1, (void *) &x1, (void *) &x2, "abc", "def", 2, "hij");
	return 0;
}

