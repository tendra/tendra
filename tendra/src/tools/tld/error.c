/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


/**** error.c --- Error reporting.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the error reporting facility specified in the file
 * "error.h".  See that file for more details.
 *
 **** Change Log:
 * $Log$
 * Revision 1.2  2002/11/21 22:31:25  nonce
 * Remove ossg prototypes.  This commit is largely whitespace changes,
 * but is nonetheless important.  Here's why.
 *
 * I.  Background
 * =========================
 *
 *     The current TenDRA-4.1.2 source tree uses "ossg" prototype
 * conventions, based on the Open Systems Software Group publication "C
 * Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 * The goal behind ossg prototypes remains admirable: TenDRA should
 * support platforms that lack ANSI compliant compilers.  The explicit
 * nature of ossg's prototypes makes macro substition easy.
 *
 *     Here's an example of one function:
 *
 *     static void uop
 * 	PROTO_N ( ( op, sha, a, dest, stack ) )
 * 	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 * 		  shape sha X exp a X where dest X ash stack )
 *     {
 *
 * tendra/src/installers/680x0/common/codec.c
 *
 *   The reasons for removing ossg are several, including:
 *
 *   0) Variables called 'X' present a problem (besides being a poor
 * variable name).
 *
 *   1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 * prototypes are easily handled by most every compiler these days.
 *
 *   2) Although TenDRA emphasizes portability, standards compliance is
 * the primary goal of the current project.  We should expect no less
 * from the compiler source code.
 *
 *   3) The benefits of complex prototypes are few, given parameter
 * promotion rules.  (Additionally, packing more types into int-sized
 * spaces tends to diminish type safety, and greatly complicates
 * debugging and testing.)
 *
 *   4) It would prove impractical to use an OSSG internal style document
 * in an open source project.
 *
 *   5) Quite frankly, ossg prototypes are difficult to read, but that's
 * certainly a matter of taste and conditioning.
 *
 * II.  Changes
 * =========================
 *
 *    This commit touches most every .h and .c file in the tendra source
 * tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 * was used to automate the following changes:
 *
 *    A.  Prototype Conversions.
 *    --------------------------------------------------
 *
 *    The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 * rewritten to ISO-compliant form.  Not every file was touched.  The
 * files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 * left for hand editing.  These files provide header generation, or have
 * non-ossg compliant headers to start with.  Scripting around these
 * would take too much time; a separate hand edit will fix them.
 *
 *    B.  Statement Spacing
 *    --------------------------------------------------
 *
 *    Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 * parenthetical lexemes.  (See the quoted example above.)  A simple
 * text substitution was made for:
 *
 *      Before            After
 * ===================================
 *
 *    if ( x )            if (x)
 *    if(x)               if (x)
 *    x = 5 ;             x = 5;
 *    ... x) )            ... x))
 *
 * All of these changes are suggested by style(9).  Additional, statement
 * spacing considerations were made for all of the style(9) keywords:
 * "if" "while" "for" "return" "switch".
 *
 * A few files seem to have too few spaces around operators, e.g.:
 *
 *       arg1*arg2
 *
 * instead of
 *
 *       arg1 * arg2
 *
 * These were left for hand edits and later commits, since few files
 * needed these changes.  (At present, the rmossg.el script takes 1 hour
 * to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 * needed change would take too much time.)
 *
 *    C.  License Information
 *    --------------------------------------------------
 *
 * After useful discussion on IRC, the following license changes were
 * made:
 *
 *    1) Absent support for $License::BSD$ in the repository, license
 * and copyright information was added to each file.
 *
 *    2) Each file begins with:
 *
 *    Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *    All rights reserved.
 *
 *    Usually, copyright stays with the author of the code; however, I
 * feel very strongly that this is a group effort, and so the tendra
 * project should claim any new (c) interest.
 *
 *    3) The comment field then shows the bsd license and warranty
 *
 *    4) The comment field then shows the Crown Copyright, since our
 * changes are not yet extensive enough to claim any different.
 *
 *    5) The comment field then closes with the $TenDRA$ tag.
 *
 *    D.  Comment Formatting
 *    --------------------------------------------------
 *
 * The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *     /*
 *        Statement statement
 *        statement
 *      */
 *
 * while style(9) suggests:
 *
 *     /*
 *      * Statement statement
 *      * statement
 *      */
 *
 * Not every comment in -4.1.2 needed changing.  A parser was written to
 * identify non-compliant comments.  Note that a few comments do not
 * follow either the TenDRA-4.1.2 style or style(9), or any style I can
 * recognize.  These need hand fixing.
 *
 *    E.  Indentation
 *    --------------------------------------------------
 *
 *    A elisp tendra-c-mode was created to define how code should be
 * indented.  The structure follows style(9) in the following regards:
 *
 *   (c-set-offset 'substatement-open 0)
 *   (setq c-indent-tabs-mode t
 * 	c-indent-level 4
 * 	c-argdecl-indent t
 * 	c-tab-always-indent t
 * 	backward-delete-function nil
 * 	c-basic-offset 4
 * 	tab-width 4))
 *
 * This means that substatement opening are not indented.  E.g.:
 *
 *    if (condition)
 *    {
 *
 * instead of
 *
 *    if (condition)
 *      {
 *
 * or even
 *
 *    if (condition) {
 *
 * Each statement is indented by a tab instead of a spaces.  Set your tab
 * stop to comply with style(9); see the vim resources in the tendra
 * tree.  I'll add the emacs mode support shortly.
 *
 * No doubt, a function or two escaped change because of unusual
 * circumstances.  These must be hand fixed as well.
 *
 * III.  Things Not Changed
 * =========================
 *
 *     A large number of style(9) deficiencies remain.  These will
 * require a separate effort.  I decided to stop with the changes noted
 * above because:
 *
 *    0)  The script currently takes hours to run to completion even on
 * high-end consumer machines.
 *
 *    1)  We need to move on and fix other substantive problems.
 *
 *    2) The goal of this commit was *just* ossg removal; I took the
 * opportunity to get other major white-space issues out of the way.
 *
 *     I'll also note that despite this commit, a few ossg issues remain.
 * These include:
 *
 *    0) The ossg headers remain.  They contain useful flags needed by
 * other operations.  Additionally, the BUILD_ERRORS perl script still
 * generates ossg-compliant headers.  (This is being removed as we change
 * the build process.)
 *
 *    1) A few patches of code check for ossg flags: "if (ossg) etc."
 * These can be hand removed as well.
 *
 *    2) No doubt, a few ossg headers escaped the elisp script.  We can
 * address these seriatim.
 *
 * IV.  Testing
 * =========================
 *
 *     Without a complete build or test suite, it's difficult to
 * determine if these changes have introduced any bugs.  I've identified
 * several situations where removal of ossg caused bugs in sid and
 * calculus operations.  The elisp script avoids these situations; we
 * will hand edit a few files.
 *
 *     As is, the changes should behave properly; the source base builds
 * the same before and after the rmossg.el script is run.  Nonetheless,
 * please note that this commit changes over 23,000 PROTO declarations,
 * and countless line changes.  I'll work closely with any developers
 * affected by this change.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:44:41  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:51  smf
 * Initial import of library shared files.
 *
 **/

/****************************************************************************/

#include "error.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#define TAG_TABLE_SIZE (127)
#define ERROR_TABLE_SIZE (127)
#define STRING_TABLE_SIZE (127)

/*--------------------------------------------------------------------------*/

static ETagP		tag_table [TAG_TABLE_SIZE];
static ErrorP		error_table [ERROR_TABLE_SIZE];
static EStringP		string_table [STRING_TABLE_SIZE];
static CStringP		program_name         = NIL (CStringP);
static ErrorInitProcP	init_proc	     = NIL (ErrorInitProcP);
static ETagP		etag_program	     = NIL (ETagP);
static ETagP		etag_severity	     = NIL (ETagP);
static ETagP		etag_error_name      = NIL (ETagP);
static ETagP		etag_dollar	     = NIL (ETagP);
static ETagP		etag_ocb	     = NIL (ETagP);
static ETagP		etag_ccb	     = NIL (ETagP);
static ErrorListP	error_prefix	     = NIL (ErrorListP);
static ESeverityT	min_severity	     = ERROR_SEVERITY_ERROR;
static ESeverityT	max_reported	     = ERROR_SEVERITY_INFORMATION;
static EStringDataT	severity_data []     = {
    UB {"error severity information",	"Info"} UE,
    UB {"error severity warning",	"Warning"} UE,
    UB {"error severity error",		"Error"} UE,
    UB {"error severity fatal",		"Fatal"} UE,
    UB {"error severity internal",	"Internal"} UE,
    ERROR_END_STRING_LIST
};

/*--------------------------------------------------------------------------*/

static void
error_deallocate_error_list(ErrorListP error_list)
{
    while (error_list) {
		ErrorListP tmp = error_list;
		
		if (error_list->tag == ERROR_TAG_STRING) {
			nstring_destroy (&(error_list->u.string));
		}
		error_list = error_list->next;
		DEALLOCATE (tmp);
    }
}

static ErrorListP
error_parse_message(CStringP message)
{
    ErrorListP  error_list;
    ErrorListP *error_list_next = &error_list;
    CStringP    message_copy    = cstring_duplicate (message);
    CStringP    scan            = message = message_copy;
	
    while (*scan) {
		if ((*scan ++ == '$') && (*scan == '{')) {
			if (scan > (message + 1)) {
				ErrorListP tmp = ALLOCATE (ErrorListT);
				
				tmp->tag  = ERROR_TAG_STRING;
				scan [-1] = '\0';
				nstring_copy_cstring (&(tmp->u.string), message);
				*error_list_next = tmp;
				error_list_next  = &(tmp->next);
			}
			scan ++;
			message = scan;
			while (*scan != '}') {
				if ((*scan == '\0') || (*scan == '$') || (*scan == '{') ||
					((!syntax_is_printable (*scan)) && (*scan != ' '))) {
					*error_list_next = NIL (ErrorListP);
					error_deallocate_error_list (error_list);
					return (NIL (ErrorListP));
				}
				scan ++;
			}
			if (scan ++ > message) {
				ErrorListP tmp = ALLOCATE (ErrorListT);
				CStringP   tag;
				
				tmp->tag   = ERROR_TAG_TAG;
				scan [-1]  = '\0';
				tag        = cstring_duplicate (message);
				tmp->u.tag = error_define_tag (tag);
				if (tmp->u.tag->name != tag) {
					DEALLOCATE (tag);
				}
				*error_list_next = tmp;
				error_list_next  = &(tmp->next);
			}
			message = scan;
		}
    }
    if (scan > message) {
		ErrorListP tmp = ALLOCATE (ErrorListT);
		
		tmp->tag = ERROR_TAG_STRING;
		nstring_copy_cstring (&(tmp->u.string), message);
		*error_list_next = tmp;
		error_list_next  = &(tmp->next);
    }
    *error_list_next = NIL (ErrorListP);
    DEALLOCATE (message_copy);
    return (error_list);
}

static void
write_error_list(OStreamP ostream, ErrorListP error_list,
				 ErrorP error, ErrorProcP proc,
				 GenericP closure)
{
    while (error_list) {
		switch (error_list->tag) EXHAUSTIVE {
		case ERROR_TAG_STRING:
			write_nstring (ostream, &(error_list->u.string));
			break;
		case ERROR_TAG_TAG:
			if (error_list->u.tag == etag_program) {
				write_cstring (ostream, program_name);
			} else if (error_list->u.tag == etag_severity) {
				EStringP estring =
					severity_data [(error->severity)].estring;
				
				write_cstring (ostream, error_string_contents (estring));
			} else if (error_list->u.tag == etag_error_name) {
				write_cstring (ostream, error->name);
			} else if (error_list->u.tag == etag_dollar) {
				write_char (ostream, '$');
			} else if (error_list->u.tag == etag_ocb) {
				write_char (ostream, '{');
			} else if (error_list->u.tag == etag_ccb) {
				write_char (ostream, '}');
			} else if (proc) {
				((*proc) (ostream, error_list->u.tag, closure));
			}
			break;
		}
		error_list = error_list->next;
    }
}

static void
write_error_list_text(OStreamP ostream, ErrorListP error_list)
{
    NStringP nstring;
    CStringP contents;
    unsigned length;
	
    write_char (ostream, '"');
    while (error_list) {
		switch (error_list->tag) EXHAUSTIVE {
		case ERROR_TAG_STRING:
			nstring  = &(error_list->u.string);
			contents = nstring_contents (nstring);
			length   = nstring_length (nstring);
			
			while (length --) {
				switch (*contents) {
				case '\n':
					write_cstring (ostream, "\\n\\");
					write_newline (ostream);
					break;
				case '"':
					write_cstring (ostream, "\\\"");
					break;
				default:
					ASSERT (*contents != '\0');
					write_char (ostream, *contents);
					break;
				}
				contents ++;
			}
			break;
		case ERROR_TAG_TAG:
			write_cstring (ostream, "${");
			write_cstring (ostream, error_list->u.tag->name);
			write_char (ostream, '}');
			break;
		}
		error_list = error_list->next;
    }
    write_char (ostream, '"');
}

static void
write_error_table(OStreamP ostream)
{
    unsigned i;
	
    for (i = 0; i < ERROR_TABLE_SIZE; i ++) {
		ErrorP error = error_table [i];
		
		while (error) {
			write_char (ostream, '\'');
			write_cstring (ostream, error->name);
			write_char (ostream, '\'');
			write_newline (ostream);
			write_cstring (ostream, "    ");
			write_error_list_text (ostream, error->error_list);
			write_newline (ostream);
			error = error->next;
		}
    }
}

static void
write_string_table(OStreamP ostream)
{
    unsigned i;
	
    for (i = 0; i < STRING_TABLE_SIZE; i ++) {
		EStringP string = string_table [i];
		
		while (string) {
			CStringP contents = string->contents;
			
			write_char (ostream, '\'');
			write_cstring (ostream, string->name);
			write_char (ostream, '\'');
			write_newline (ostream);
			write_cstring (ostream, "    ");
			write_char (ostream, '"');
			while (*contents) {
				switch (*contents) {
				case '\n':
					write_cstring (ostream, "\\n\\");
					write_newline (ostream);
					break;
				case '"':
					write_cstring (ostream, "\\\"");
					break;
				default:
					write_char (ostream, *contents);
					break;
				}
				contents ++;
			}
			write_char (ostream, '"');
			write_newline (ostream);
			string = string->next;
		}
    }
}

/*--------------------------------------------------------------------------*/

void
error_init(CStringP name, ErrorInitProcP proc)
{
    static CStringP prefix = "${program name}: ${severity}: ";
	
    program_name = name;
    while (*name) {
		if (*name ++ == '/') {
			program_name = name;
		}
    }
    init_proc       = proc;
    etag_program    = error_define_tag ("program name");
    etag_severity   = error_define_tag ("severity");
    etag_error_name = error_define_tag ("this error name");
    etag_dollar     = error_define_tag ("dollar");
    etag_ocb        = error_define_tag ("open brace");
    etag_ccb        = error_define_tag ("close brace");
    error_prefix    = error_parse_message (prefix);
    error_intern_strings (severity_data);
    ostream_buffer (ostream_error);
}

void
error_call_init_proc()
{
    if (init_proc) {
		(*init_proc) ();
		init_proc = NIL (ErrorInitProcP);
    }
}

ETagP
error_define_tag(CStringP name)
{
    unsigned hash   = (cstring_hash_value (name) % TAG_TABLE_SIZE);
    ETagP   *entryp = &(tag_table [hash]);
    ETagP    entry;
	
    while ((entry = *entryp) != NIL (ETagP)) {
		if (cstring_equal (entry->name, name)) {
			return (entry);
		}
		entryp = &(entry->next);
    }
    entry       = ALLOCATE (ETagT);
    entry->next = NIL (ETagP);
    entry->name = name;
    *entryp     = entry;
    return (entry);
}

ErrorP
error_define_error(CStringP name, ESeverityT severity,
				   CStringP message, GenericP data)
{
    ErrorListP error_list = error_parse_message (message);
    unsigned   hash       = (cstring_hash_value (name) % ERROR_TABLE_SIZE);
    ErrorP    *entryp     = &(error_table [hash]);
    ErrorP     entry;
	
    while ((entry = *entryp) != NIL (ErrorP)) {
		ASSERT (!cstring_equal (entry->name, name));
		entryp = &(entry->next);
    }
    ASSERT (error_list);
    entry             = ALLOCATE (ErrorT);
    entry->next       = NIL (ErrorP);
    entry->name       = name;
    entry->severity   = severity;
    entry->error_list = error_list;
    entry->data       = data;
    *entryp           = entry;
    return (entry);
}

void
error_intern_tags(ETagDataP vector)
{
    while (vector->name) {
		ETagP tag = error_define_tag (vector->name);
		
		vector->tag = tag;
		vector ++;
    }
}

void
error_intern_errors(ErrorDataP vector)
{
    while (vector->s.name) {
		ErrorP error = error_define_error (vector->s.name, vector->s.severity,
										   vector->s.message, vector->s.data);
		
		vector->error = error;
		vector ++;
    }
}

ErrorStatusT
error_redefine_error(CStringP name, CStringP message)
{
    error_call_init_proc ();
    {
		unsigned hash  = (cstring_hash_value (name) % ERROR_TABLE_SIZE);
		ErrorP   entry = (error_table [hash]);
		
		while (entry) {
			if (cstring_equal (entry->name, name)) {
				ErrorListP error_list = error_parse_message (message);
				
				if (error_list == NIL (ErrorListP)) {
					return (ERROR_STATUS_BAD_MESSAGE);
				}
				error_deallocate_error_list (entry->error_list);
				entry->error_list = error_list;
				return (ERROR_STATUS_SUCCESS);
			}
			entry = entry->next;
		}
		return (ERROR_STATUS_BAD_ERROR);
    }
}

ErrorP
error_lookup_error(CStringP name)
{
    error_call_init_proc ();
    {
		unsigned hash  = (cstring_hash_value (name) % ERROR_TABLE_SIZE);
		ErrorP   entry = (error_table [hash]);
		
		while (entry) {
			if (cstring_equal (entry->name, name)) {
				return (entry);
			}
			entry = entry->next;
		}
		return (NIL (ErrorP));
    }
}

GenericP
error_data(ErrorP error)
{
    return (error->data);
}

void
error_report(ErrorP error, ErrorProcP proc,
			 GenericP closure)
{
    if ((error->severity) >= min_severity) {
		write_error_list (ostream_error, error_prefix, error, NIL (ErrorProcP),
						  NIL (GenericP));
		write_error_list (ostream_error, error->error_list, error, proc,
						  closure);
		write_newline (ostream_error);
		ostream_flush (ostream_error);
    }
    if ((error->severity) > max_reported) {
		max_reported = error->severity;
    }
    if ((error->severity) >= ERROR_SEVERITY_FATAL) {
		if (error->severity == ERROR_SEVERITY_INTERNAL) {
			abort ();
			UNREACHED;
		}
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

void
error_set_min_report_severity(ESeverityT severity)
{
    min_severity = severity;
}

ESeverityT
error_get_min_report_severity()
{
    return (min_severity);
}

ESeverityT
error_max_reported_severity()
{
    return (max_reported);
}

void
error_set_severity_message(ESeverityT severity,
						   CStringP message)
{
    severity_data [severity].estring->contents = message;
}

BoolT
error_set_prefix_message(CStringP message)
{
    ErrorListP error_list = error_parse_message (message);
	
    if (error_list == NIL (ErrorListP)) {
		return (FALSE);
    }
    error_deallocate_error_list (error_prefix);
    error_prefix = error_list;
    return (TRUE);
}

EStringP
error_define_string(CStringP name, CStringP contents)
{
    unsigned  hash   = (cstring_hash_value (name) % STRING_TABLE_SIZE);
    EStringP *entryp = &(string_table [hash]);
    EStringP  entry;
	
    while ((entry = *entryp) != NIL (EStringP)) {
		ASSERT (!cstring_equal (entry->name, name));
		entryp = &(entry->next);
    }
    entry           = ALLOCATE (EStringT);
    entry->next     = NIL (EStringP);
    entry->name     = name;
    entry->contents = contents;
    *entryp         = entry;
    return (entry);
}

void
error_intern_strings(EStringDataP vector)
{
    while (vector->s.name) {
		EStringP estring = error_define_string (vector->s.name,
												vector->s.contents);
		
		vector->estring = estring;
		vector ++;
    }
}

BoolT
error_redefine_string(CStringP name, CStringP contents)
{
    unsigned hash  = (cstring_hash_value (name) % STRING_TABLE_SIZE);
    EStringP entry = (string_table [hash]);
	
    while (entry) {
		if (cstring_equal (entry->name, name)) {
			entry->contents = contents;
			return (TRUE);
		}
		entry = entry->next;
    }
    return (FALSE);
}

EStringP
error_lookup_string(CStringP name)
{
    unsigned hash  = (cstring_hash_value (name) % STRING_TABLE_SIZE);
    EStringP entry = (string_table [hash]);
	
    while (entry) {
		if (cstring_equal (entry->name, name)) {
			return (entry);
		}
		entry = entry->next;
    }
    return (NIL (EStringP));
}

CStringP
error_string_contents(EStringP estring)
{
    return (estring->contents);
}

void
write_error_file(OStreamP ostream)
{
    error_call_init_proc ();
    write_cstring (ostream, "%prefix%");
    write_newline (ostream);
    write_cstring (ostream, "    ");
    write_error_list_text (ostream, error_prefix);
    write_newline (ostream);
    write_newline (ostream);
    write_cstring (ostream, "%errors%");
    write_newline (ostream);
    write_error_table (ostream);
    write_newline (ostream);
    write_cstring (ostream, "%strings%");
    write_newline (ostream);
    write_string_table (ostream);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
 **/
