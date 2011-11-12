/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:24 $
$Revision: 1.1.1.1 $
$Log: includes.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:16  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#include "util.h"
#include "includes.h"
#include "errors.h"

#include <shared/xalloc.h>

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
