/*
 * Copyright (c) 2003-2004, by Boris Popov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $TenDRA$
 */
#include <signal.h>

#include "config.h"
#include "fmm.h"
#include "msgcat.h"
#include "ostream.h"
#include "release.h"
#include "tenapp.h"

/*
 * This file provides common execution environment for all TenDRA programs.
 */

struct exit_handler {
	tenapp_eh_t *		eh;
	struct exit_handler *	next;
};

/*
 * progname can be set manually or extracted from argv
 */
const char *progname = "amnesiac";

/*
 * progvers represents internal program version
 */
const char *progvers = "0.0";

/*
 * Human readable program description
 */
const char *progdesc = "tenapp";

/*
 * release version common for an entire package
 */
const char *relvers = RELEASE;

/*
 * Dump memory allocation statistic in tenapp_exit()
 */
int tenapp_print_memusage_onexit = 0;

/*
 * Exit status for tenapp_exit()
 */
int exit_status;

/*
 * Don't delete core file if signal caught
 */
int keep_core = 1;

/*
 * Last executed command from which we may receive signal
 */
const char *last_command;

struct fmm_type *memtype_app;

static struct exit_handler *exit_list;

void
tenapp_signal(int sig)
{
	signal(SIGINT, SIG_IGN);
	if (sig != SIGINT) {
		const char *cmd = (last_command ? last_command : progname);
		MSG_caught_signal(sig, cmd);
		if (!keep_core && (remove ("core") == 0)) {
			MSG_removed_core();
		}
	}
	tenapp_exit2(EXIT_FAILURE);
}

/*
 * Perform initial setup of application environment
 */
void
tenapp_init(int argc, char *argv[], const char *pdesc, const char *pver)
{
	UNUSED(argc);
	progdesc = pdesc;
	progvers = pver;

	ostream_setup();	/* standard output streams */
	msg_init();		/* message catalog */

	memtype_app = fmm_type_add("Application", "Application data");

	/*
	 * Catchup signals to shutdown gracefully
	 */
	signal(SIGINT, tenapp_signal);
	signal(SIGSEGV, tenapp_signal);
	signal(SIGTERM, tenapp_signal);
#ifdef SIGFPE
	signal(SIGFPE, tenapp_signal);
#endif
	set_progname(argv[0]);
}

/*
 * Check if errors severity exceeded given level and exit if so.
 */
void
tenapp_checkerrors(int sl)
{
	if (msg_max_reported_severity >= sl) {
		tenapp_exit2(EXIT_FAILURE);
		UNREACHED;
	}
}

/*
 * Perform cleanup and exit
 */
void
tenapp_exit(void)
{
	struct exit_handler *ep;

	if (tenapp_print_memusage_onexit)
		fmm_stat_by_type();
	for (ep = exit_list; ep; ep = ep->next)
		ep->eh();
#ifdef __WIN32__
	fmm_freeall();
#endif
	exit(exit_status);
}

void
tenapp_exit2(int es)
{
	exit_status = es;
	tenapp_exit();
}

void
tenapp_add_eh(tenapp_eh_t *eh)
{
	struct exit_handler *ep;

	ep = fmm_malloc(sizeof(*ep), memtype_app);
	ep->eh = eh;
	ep->next = exit_list;
	exit_list = ep;
}


/*
 * This routine sets the program name to the basename of prog and the
 * program version to vers. Any of them can be NULL.
 */
void
set_progname(const char *prog)
{
	char *s;

	if (prog) {
		s = strrchr(prog, FS_PATH_SEP);
		if (s)
			prog = s + 1;
		progname = prog;
	}
}

void
tenapp_report_version(void)
{
	MSG_tenapp_version(progdesc, progvers, relvers);
}

