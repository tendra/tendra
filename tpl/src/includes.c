/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/xalloc.h>

#include "config.h"

#include "util.h"
#include "includes.h"
#include "errors.h"

char *file_name;
static Path *inc_paths;


void
init_includes(void)
{
	inc_paths = xmalloc(sizeof *inc_paths);
	inc_paths->name = "";
	inc_paths->next = (Path *)0;
}


void
add_include(char *p)
{
	Path *x = xmalloc(sizeof *x);
	Path **n = &inc_paths->next;
	x->name = append_string(p, "/");
	x->next = (Path *)0;
	while (*n != (Path *)0)n = &((*n)->next);
	*n = x;
}


FILE *
open_include(char * a)
{
	char *fn;
	Path *p = inc_paths;
	FILE *ans;
	int i;
	while (*a != '"') {
		a++;
	}
	a++;
	for (i = 0;; i++) {
		if (a[i] =='"' || a[i] ==0) {
			a[i] = 0;
			break;
		}
	}
	while (p != (Path *)0) {
		fn = append_string(p->name, a);
		ans = fopen(fn, "r");
		if (ans != (FILE *)0) {
			file_name = fn;
			return ans;
		}
		p = p->next;
	}
	fail("Can't open include file %s", a);
	return (FILE *)0;
}
