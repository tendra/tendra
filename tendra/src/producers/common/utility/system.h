/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef SYSTEM_INCLUDED
#define SYSTEM_INCLUDED


/*
 *    POSIX DEPENDENT TYPES
 *
 *    These definitions give the POSIX types required in this module.
 *    Dummy definitions for non-POSIX systems are also given.  The default
 *    value for FS_POSIX is given in ossg_api.h.  The loss in functionality
 *    with the non-POSIX definitions is minimal (#import may not work in
 *    obscure cases, the file datestamps in diagnostics mode may be wrong).
 */

#if FS_POSIX

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#if FS_UTSNAME
#include <sys/utsname.h>
#endif

typedef struct stat STAT_TYPE;

#else /* FS_POSIX */

#include <time.h>

typedef struct {
    time_t st_mtime;
    unsigned long st_dev;
    unsigned long st_ino;
} STAT_TYPE;

#endif /* FS_POSIX */


/*
 *    SYSTEM FUNCTION DECLARATIONS
 *
 *    The routines in this module are used to interface to the underlying
 *    operating system.
 */

extern CONST char *find_date(CONST char *);
extern CONST char *find_time(CONST char *);
extern STAT_TYPE *stat_func(char *, STAT_TYPE *);
extern unsigned long stat_date(STAT_TYPE *);
extern int stat_equal(STAT_TYPE *, STAT_TYPE *);
extern int file_seek(FILE *, long);
extern CONST char *find_cwd(void);
extern CONST char *find_machine(void);

extern unsigned long crt_time;
extern char uniq_string [];
extern int binary_mode;
extern int text_mode;
extern int good_fseek;
extern int good_stat;
extern int drive_sep;
extern int file_sep;


#endif
