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
#ifdef TDF_DIAG3
#include <dwarf1/dw1_version.h>
#endif
#include <dwarf2/dw2_version.h>

#include <shared/error.h>

#include <main/flags.h>
#include <main/driver.h>

void
trans_version(void)
{
	size_t i;

	struct {
		const char *name;
		int major;
		int minor;
		const char *spec;
		int diag;
	} a[] = {
#ifdef TDF_DIAG3
		{ "DWARF1",    DWARF1_MAJOR,      DWARF1_MINOR,       NULL,         DIAG_DWARF1 },
#endif
#ifdef DWARF2
		{ "DWARF2",    DWARF2_MAJOR,      DWARF2_MINOR,       NULL,         DIAG_DWARF2 },
#endif
#ifndef TDF_DIAG4
		{ "diag3",     diag_version,      diag_revision,      DG_VERSION,   0           },
#endif
#ifdef TDF_DIAG4
		{ "diag4",     diag_version,      diag_revision,      NULL,         0           },
#endif
		{ "reader",    reader_version,    reader_revision,    NULL,         0           },
		{ "construct", construct_version, construct_revision, NULL,         0           },
		{ "TDF",       MAJOR_VERSION,     MINOR_VERSION,      "def_4_1.db", 0           }
	};

	report_version(stderr);

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (a[i].diag != 0 && (driver.diag & a[i].diag) == 0) {
			continue;
		}

		fprintf(stderr, "\t%-10s %d.%d", a[i].name, a[i].major, a[i].minor);

		if (a[i].spec != NULL) {
			fprintf(stderr, ", %s", a[i].spec);
		}

		fprintf(stderr, "\n");
	}
}

