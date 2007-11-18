/*
 * Unit tests for the dstring API.
 *
 * $Id$
 */

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include <harness.h>

#include "common.h"
#include "exception.h"
#include "dstring.h"
#include "dalloc.h"

static size_t n[] = { 0, 1, 2, 5, 10, 127, 128, 129, 254, 255, 256, 257, 1027 };
static char c[]   = { '\0', '\01', '0', 'x', 'Y', '\037', '\xff', '\x7f' };
static char *s[]  = { "", "s", "ss", "abc", "abcdef", "a b", "a \01'", "a \01b",
	"They dined on mince, and slices of quince,\n"
	"Which they ate with a runcible spoon." };

static bool test_destroyc(void *opaque) {
	size_t k;

	for(k = 1; k < sizeof s / sizeof *s; k++) {
		struct DStringT dstring;
		char *cs;
		bool equal;

		dstring_init(&dstring);
		dstring_append_cstring(&dstring, s[k]);
		cs = dstring_destroy_to_cstring(&dstring);

		equal = !strncmp(cs, s[k], strlen(s[k]));

		DEALLOCATE(cs);

		if(!equal) {
			return false;
		}
	}

	return true;
}

static bool test_tocstring(void *opaque) {
	size_t k;

	for(k = 1; k < sizeof s / sizeof *s; k++) {
		struct DStringT dstring;
		char *cs;
		bool equal;

		dstring_init(&dstring);
		dstring_append_cstring(&dstring, s[k]);
		cs = dstring_to_cstring(&dstring);

		equal = !strncmp(cs, s[k], strlen(s[k]));

		DEALLOCATE(cs);
		dstring_destroy(&dstring);

		if(!equal) {
			return false;
		}
	}

	return true;
}

static bool test_tonstring(void *opaque) {
	size_t k;

	for(k = 1; k < sizeof s / sizeof *s; k++) {
		struct DStringT dstring;
		struct NStringT nstring;
		bool equal;

		dstring_init(&dstring);
		nstring_init(&nstring);
		dstring_append_cstring(&dstring, s[k]);
		dstring_to_nstring(&dstring, &nstring);

		equal = !strncmp(nstring_contents(&nstring), s[k], strlen(s[k]));

		nstring_destroy(&nstring);
		dstring_destroy(&dstring);

		if(!equal) {
			return false;
		}
	}

	return true;
}

static bool test_lastchar(void *opaque) {
	size_t i, j, k;

	for(i = 0; i < sizeof n / sizeof *n; i++) {
		struct DStringT dstring;
		bool equal;

		dstring_init(&dstring);

		for(k = 0; k < sizeof c / sizeof *c; k++) {
			for(j = 0; j <= n[i]; j++) {
				dstring_append_char(&dstring, c[k]);
			}

			if(!dstring_last_char_equal(&dstring, c[k])) {
				dstring_destroy(&dstring);
				return false;
			}
		}

		equal = dstring_last_char_equal(&dstring, c[k - 1]);

		dstring_destroy(&dstring);

		if(!equal) {
			return false;
		}
	}

	return true;
}

static bool test_appendn(void *opaque) {
	size_t i, j, k;

	for(i = 0; i < sizeof n / sizeof *n; i++) {
		struct DStringT dstring;
		unsigned int length, targetlength;

		dstring_init(&dstring);
		targetlength = 0;

		for(k = 0; k < sizeof s / sizeof *s; k++) {
			for(j = 0; j <= n[i]; j++) {
				struct NStringT nstring;

				nstring_copy_cstring(&nstring, s[k]);
				dstring_append_nstring(&dstring, &nstring);
				nstring_destroy(&nstring);
				targetlength += strlen(s[k]);
			}

			length = dstring_length(&dstring);

			if(length != targetlength) {
				return false;
			}
		}

		dstring_destroy(&dstring);
	}

	return true;
}

static bool test_appends(void *opaque) {
	size_t i, j, k;

	for(i = 0; i < sizeof n / sizeof *n; i++) {
		struct DStringT dstring;
		unsigned int length, targetlength;

		dstring_init(&dstring);
		targetlength = 0;

		for(k = 0; k < sizeof s / sizeof *s; k++) {
			for(j = 0; j <= n[i]; j++) {
				dstring_append_cstring(&dstring, s[k]);
				targetlength += strlen(s[k]);
			}

			length = dstring_length(&dstring);

			if(length != targetlength) {
				return false;
			}
		}

		dstring_destroy(&dstring);
	}

	return true;
}

static bool test_appendc(void *opaque) {
	size_t i, j, k;

	for(i = 0; i < sizeof n / sizeof *n; i++) {
		struct DStringT dstring;
		unsigned int length, targetlength;

		dstring_init(&dstring);
		targetlength = 0;

		for(k = 0; k < sizeof c / sizeof *c; k++) {
			for(j = 0; j <= n[i]; j++) {
				dstring_append_char(&dstring, c[k]);
				targetlength++;
			}

			length = dstring_length(&dstring);

			if(length != targetlength) {
				return false;
			}
		}

		dstring_destroy(&dstring);

		if(length != j * k) {
			return false;
		}
	}

	return true;
}

static bool test_empty(void *opaque) {
	struct DStringT dstring;
	unsigned int length;

	dstring_init(&dstring);

	length = dstring_length(&dstring);

	dstring_destroy(&dstring);

	return length == 0;
}

struct harness_test harness_tests[] = {
	{ true, test_empty,     "empty",     NULL },
	{ true, test_appendc,   "appendc",   NULL },
	{ true, test_appends,   "appends",   NULL },
	{ true, test_appendn,   "appendn",   NULL },
	{ true, test_lastchar,  "lastchar",  NULL },
	{ true, test_tonstring, "tonstring", NULL },
	{ true, test_tocstring, "tocstring", NULL },
	{ true, test_destroyc,  "destroyc",  NULL }
};

HARNESS_COUNT(harness_tests);

