/* $Id$ */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <utility/prefix.h>

/* XXX: stopgap until these are passed as arguments */
extern char *name_prefix;
extern char *local_prefix;

char *
add_prefix(const char *prefix, char *s)
{
	char *r;

	if (*prefix == '\0') {
		return s;
	}

	r = xmalloc(strlen(prefix) + strlen(s) + 1);
	IGNORE sprintf(r, "%s%s", prefix, s);

	return r;
}

