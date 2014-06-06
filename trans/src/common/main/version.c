/* $Id$ */

#include <stdio.h>

#include <construct/installglob.h>
#include <construct/version.h>
#include <reader/version.h>
#ifndef NEWDIAGS
#include <diag/version.h>
#endif
#ifdef NEWDIAGS
#include <newdiag/version.h>
#endif
#include <dwarf/version.h>
#include <dwarf2/version.h>

#include <shared/error.h>

void
trans_version(void)
{
	size_t i;

	struct {
		const char *name;
		int major;
		int minor;
		const char *spec;
	} a[] = {
#if (DWARF == 1)
		{ "DWARF",     DWARF_MAJOR,       DWARF_MINOR,        NULL         },
#endif
#ifdef NEWDWARF
		{ "DWARF2",    DWARF2_MAJOR,      DWARF2_MINOR,       NULL         },
#endif
#ifndef NEWDIAGS
		{ "diag",      diag_version,      diag_revision,      DG_VERSION   },
#endif
#ifdef NEWDIAGS
		{ "newdiag",   diag_version,      diag_revision,      DG_VERSION   },
#endif
		{ "reader",    reader_version,    reader_revision,    NULL         },
		{ "construct", construct_version, construct_revision, NULL         },
		{ "TDF",       MAJOR_VERSION,     MINOR_VERSION,      "def_4_1.db" }
	};

	report_version();

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		fprintf(stderr, "\t%-10s %d.%d", a[i].name, a[i].major, a[i].minor);

		if (a[i].spec != NULL) {
			fprintf(stderr, ", %s", a[i].spec);
		}

		fprintf(stderr, "\n");
	}
}

