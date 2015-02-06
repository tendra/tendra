/* $Id$ */

#include <stdio.h>

#include <construct/installglob.h>
#include <construct/version.h>
#include <reader/version.h>
#ifndef TDF_DIAG4
#include <diag3/version.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/version.h>
#endif
#include <dwarf1/dw1_version.h>
#include <dwarf2/dw2_version.h>

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
		{ "DWARF1",    DWARF1_MAJOR,      DWARF1_MINOR,       NULL         },
#endif
#ifdef DWARF2
		{ "DWARF2",    DWARF2_MAJOR,      DWARF2_MINOR,       NULL         },
#endif
#ifndef TDF_DIAG4
		{ "diag3",     diag_version,      diag_revision,      DG_VERSION   },
#endif
#ifdef TDF_DIAG4
		{ "diag4",     diag_version,      diag_revision,      NULL         },
#endif
		{ "reader",    reader_version,    reader_revision,    NULL         },
		{ "construct", construct_version, construct_revision, NULL         },
		{ "TDF",       MAJOR_VERSION,     MINOR_VERSION,      "def_4_1.db" }
	};

	report_version(stderr);

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		fprintf(stderr, "\t%-10s %d.%d", a[i].name, a[i].major, a[i].minor);

		if (a[i].spec != NULL) {
			fprintf(stderr, ", %s", a[i].spec);
		}

		fprintf(stderr, "\n");
	}
}

