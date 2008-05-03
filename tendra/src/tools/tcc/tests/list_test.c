/*
 * tcc/list.c unit tests.
 * $Id$
 */

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../list.h"

/*
 * Hacks for things we don't use here.
 * These provide symbols for the dependencies of list.c.
 * TODO can these be reworked somehow?
 */
#include "../config.h"
boolean checker;
boolean warnings;
char **env_paths;
#include "../options.h"
optmap environ_optmap[3];

void main_end(void) {
	exit(EXIT_FAILURE);
}

static char *s[] = {	/* TODO const */
	"",
	"a",
	"ab",
	"abc",
	"abc def hij"
};

static void addstr(unsigned int n) {
	size_t i, j;
	list *l;
	list *p;

 	l = NULL;
	for (i = 0; i < sizeof s / sizeof *s; i++) {
		for (j = 0; j <= n; j++) {
			l = add_item(l, s[i]);
			assert(l != NULL);
		}
	}

	p = l;
	for (i = 0; i < sizeof s / sizeof *s; i++) {
		for (j = 0; j <= n; j++) {
			assert(p != NULL);
			assert(0 == strcmp(p->item.s, s[i]));
			p = p->next;
		}
	}
	assert(p == NULL);

	free_list(l);
}

static void insertstr(unsigned int n) {
	size_t i, j;
	list *l;
	list *p;

	l = NULL;
	for (i = 0; i < sizeof s / sizeof *s; i++) {
		for (j = 0; j <= n; j++) {
			l = insert_item(s[i], l);
			assert(l != NULL);
		}
	}

	p = l;
	for (i = sizeof s / sizeof *s; i > 0; i--) {
		for (j = 0; j <= n; j++) {
			assert(p != NULL);
			assert(0 == strcmp(p->item.s, s[i - 1]));
			p = p->next;
		}
	}
	assert(p == NULL);

	free_list(l);
}

static void joinstr(unsigned int n) {
	size_t i, j;
	list *l;
	list *m;
	list *p;
	list *q;

 	l = NULL;
	for (i = 0; i < sizeof s / sizeof *s; i++) {
		for (j = 0; j <= n; j++) {
			l = add_item(l, s[i]);
			assert(l != NULL);
		}
	}

	m = NULL;
	for (i = 0; i < sizeof s / sizeof *s; i++) {
		for (j = 0; j <= n; j++) {
			m = insert_item(s[i], m);
			assert(m != NULL);
		}
	}

	q = add_list(l, m);
	assert(q != NULL);

	p = q;
	for (i = 0; i < sizeof s / sizeof *s; i++) {
		for (j = 0; j <= n; j++) {
			assert(p != NULL);
			assert(0 == strcmp(p->item.s, s[i]));
			p = p->next;
		}
	}

	for (i = sizeof s / sizeof *s; i > 0; i--) {
		for (j = 0; j <= n; j++) {
			assert(p != NULL);
			assert(0 == strcmp(p->item.s, s[i - 1]));
			p = p->next;
		}
	}
	assert(p == NULL);

	free_list(q);
}

int main(void) {
	unsigned int n[] = { 1, 2, 3, 10, 16, 255, 256, 1024, 1025, 1026 };
	size_t i;

	/*
	 * TODO: test insert_inorder() and make_list().
	 */

	for (i = 0; i < sizeof n / sizeof *n; i++) {
		/* Operations on string items */
		addstr(n[i]);
		insertstr(n[i]);
		joinstr(n[i]);
	}

	return 0;
}

