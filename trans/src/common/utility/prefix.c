/* $Id$ */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <utility/prefix.h>

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

