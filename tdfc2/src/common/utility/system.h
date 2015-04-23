/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef SYSTEM_INCLUDED
#define SYSTEM_INCLUDED


/*
    POSIX DEPENDENT TYPES

    These definitions give the POSIX types required in this module.
    Dummy definitions for non-POSIX systems are also given.

    The loss in functionality with the non-POSIX definitions is minimal
    (#import may not work in obscure cases, the file datestamps in
    diagnostics mode may be wrong).

    The default value for _POSIX_SOURCE is true under __TenDRA__ and false
    otherwise. The idea here is to reduce dependencies during bootstrap
    (where the system compiler is used), as the POSIX-related features
    are not relevant there. Then, the full functionality is provided
    (and introduces the dependency on POSIX) when building for real.
*/

#if _POSIX_SOURCE

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <time.h>

typedef struct stat STAT_TYPE;

#else

#include <time.h>

typedef struct {
	time_t st_mtime;
	unsigned long st_dev;
	unsigned long st_ino;
} STAT_TYPE;

#endif


/*
    SYSTEM FUNCTION DECLARATIONS

    The routines in this module are used to interface to the underlying
    operating system.
*/

extern const char *find_date(const char *);
extern const char *find_time(const char *);
extern STAT_TYPE *stat_func(char *, STAT_TYPE *);
extern unsigned long stat_date(STAT_TYPE *);
extern int stat_equal(STAT_TYPE *, STAT_TYPE *);
extern int file_seek(FILE *, long);
extern const char *find_cwd(void);

extern unsigned long crt_time;
extern char uniq_string[];
extern int binary_mode;
extern int text_mode;
extern int drive_sep;
extern int file_sep;
extern const char *machine_name;


#endif
