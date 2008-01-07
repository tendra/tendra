/*
 * Copyright (c) 2004, The Tendra Project <http://www.ten15.org/>
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


#ifndef TEN_MSGCAT_H
#define TEN_MSGCAT_H

#include <ctype.h>
#include <stddef.h>

#define	MSGCAT_MAXPARAMS	10


/*
 * Default print function for messages
 */
#ifndef	MSG_GEN
#define	MSG_GEN		msg_print
#endif

/*
 * Pull in program specific catalog
 */
#ifndef MSG_NO_CATSTD
#include "catstd.h"
#endif

/*
 * User defined function for application specific  types
 */
typedef void msg_uh_t (char, void *);

/*
 * Type of msg_on_message handler
 */
typedef void msg_on_message_t (MSG_DATA *);

struct OStreamT;


void  msg_init(void);
void  msg_print(int, ...);
const char *msg_get_raw(int);
void  msg_simple(const char *s, ...);
void  msg_sev_set(int, int);
void  msg_sev_stream(int, struct OStreamT *);
void  msg_append_char(char);
void  msg_append_string(const char *);
void  msg_append_nstring(const char *, size_t);
void  msg_append_newline(void);
void  msg_uh_add(char, msg_uh_t *);

/*
 * Set this to zero if no program prefix required
 */
extern int msgcat_show_progname;

/*
 * Maximum message severity level ever reported
 */
extern int msg_max_reported_severity;

/*
 * User handler called before message is printed
 */
extern msg_on_message_t *msg_on_message;

extern struct OStreamT *msg_stream;

extern int crt_line_no;
extern const char *crt_file_name;


/*
 * ASSERTION ROUTINE DECLARATIONS
 *
 * These macros are used to define assertions for aiding program
 * development.  If the macro ASSERTS is defined then code for checking
 * these assertions is output, otherwise the macros have no effect.
 * Note that ASSERTS is automatically defined if DEBUG is (see config.h).
 * FAIL_COMPILER is intended as an alternative to #error blows up some
 * compilers even if it is not on the main compilation path.
 */


#ifdef DEBUG
# define ASSERTS		1
# define RUNTIME		1
#endif

#ifdef ASSERTS

int is_true(int);
void assertion(const char *, const char *, int);

# define ASSERT(A)	if (is_true (!(A)))\
			    assertion (#A, __FILE__, __LINE__)
# define FAIL(A)	assertion (#A, __FILE__, __LINE__)
#else
# if FS_LINT
#  define ASSERT(A)	/* empty */
#  define FAIL(A)	/* empty */
# else
#  define ASSERT(A)	(IGNORE 0)
#  define FAIL(A)	(IGNORE 0)
# endif
#endif

/* Compile-time assertion */
#define CT_ASSERT(A)	(IGNORE sizeof (int [(A) ? 1 : -1]))

#ifndef __FILE__
#define	__FILE__	"unknown"
#endif

#ifndef __LINE__
#define	__LINE__	1
#endif


#endif /* !MSGCAT_H */
