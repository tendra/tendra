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


/*** name-key.c --- External name key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the external name key routines used by the TDF linker.
 *
 *** Change Log:
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
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:28  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:38  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:35  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
 **/

/****************************************************************************/

#include "name-key.h"
#include "syntax.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static BoolT
name_key_parse_hex_char(CStringP name, char *c_ref)
{
    char result;
    char c;
    int  value;
	
    if ((c = name [0]), ((value = syntax_value (c)) != SYNTAX_NO_VALUE)) {
		result = (char) ((unsigned) value << 4);
    } else {
		return (FALSE);
    }
    if ((c = name [1]), ((value = syntax_value (c)) != SYNTAX_NO_VALUE)) {
		result |= (char) value;
    } else {
		return (FALSE);
    }
    *c_ref = result;
    return (TRUE);
}

static BoolT
name_key_parse_escaped(CStringP *name_ref,
					   char *c_ref)
{
    CStringP name = (*name_ref);
	
    switch ((*++ name)) {
	case 'x': case 'X':
		if (!name_key_parse_hex_char (name, c_ref)) {
			return (FALSE);
		}
		name += 3;
		break;
	case 'n': case 'N':
		*c_ref = '\n';
		name ++;
		break;
	case 'r': case 'R':
		*c_ref = '\r';
		name ++;
		break;
	case 't': case 'T':
		*c_ref= '\t';
		name ++;
		break;
	case '0':
		*c_ref = '\0';
		name ++;
		break;
	case '\\': case '.': case '[': case ']':
		*c_ref = *name ++;
		break;
	default:
		return (FALSE);
    }
    *name_ref = name;
    return (TRUE);
}

static BoolT
name_key_parse_cstring_unique(NameKeyP key,
							  CStringP name)
{
    unsigned length   = 1;
    CStringP tmp_name = name;
    NStringP components;
    unsigned i;
	
    while (*++ tmp_name) {
		if (*tmp_name == '.') {
			length ++;
		}
    }
    components = ALLOCATE_VECTOR (NStringT, length);
    length     = 0;
    for (;;) {
		DStringT dstring;
		
		name ++;
		dstring_init (&dstring);
		while ((*name != '.') && (*name != ']')) {
			if ((*name == '\0') || (*name == '[')) {
				dstring_destroy (&dstring);
				goto fail;
			} else if (*name == '\\') {
				char c;
				
				if (name_key_parse_escaped (&name, &c)) {
					dstring_append_char (&dstring, c);
				} else {
					dstring_destroy (&dstring);
					goto fail;
				}
			} else {
				dstring_append_char (&dstring, *name ++);
			}
		}
		dstring_to_nstring (&dstring, &(components [length ++]));
		if (*name == ']') {
			break;
		}
    }
    if (*name) {
      fail:
		for (i = 0; i < length ; i ++) {
			nstring_destroy (&(components [i]));
		}
		DEALLOCATE (components);
		return (FALSE);
    }
    name_key_init_unique (key, length);
    for (i = 0; i < length; i ++) {
		name_key_set_component (key, i, &(components [i]));
    }
    DEALLOCATE (components);
    return (TRUE);
}

static BoolT
name_key_parse_cstring_string(NameKeyP key,
							  CStringP name)
{
    DStringT dstring;
    NStringT nstring;
	
    dstring_init (&dstring);
    while (*name) {
		if ((*name == '[') || (*name == ']') || (*name == '.')) {
			dstring_destroy (&dstring);
			return (FALSE);
		} else if (*name == '\\') {
			char c;
			
			if (name_key_parse_escaped (&name, &c)) {
				dstring_append_char (&dstring, c);
			} else {
				dstring_destroy (&dstring);
				return (FALSE);
			}
		} else {
			dstring_append_char (&dstring, *name ++);
		}
    }
    dstring_to_nstring (&dstring, &nstring);
    name_key_init_string (key, &nstring);
    return (TRUE);
}

static void
write_name_key_1(OStreamP ostream, NStringP nstring)
{
    unsigned length = nstring_length (nstring);
    CStringP bytes  = nstring_contents (nstring);
	
    while (length --) {
		switch (*bytes) {
		case '[': case ']': case '.': case '\\':
			write_char (ostream, '\\');
			FALL_THROUGH;
		default:
			write_char (ostream, *bytes);
		}
		bytes ++;
    }
}

/*--------------------------------------------------------------------------*/

void
name_key_init_string(NameKeyP key, NStringP string)
{
    key->type = KT_STRING;
    nstring_assign (&(key->u.string), string);
}

void
name_key_init_unique(NameKeyP key, unsigned components)
{
    key->type                = KT_UNIQUE;
    key->u.unique.length     = components;
    key->u.unique.components = ALLOCATE_VECTOR (NStringT, components);
}

BoolT
name_key_parse_cstring(NameKeyP key, CStringP name)
{
    if (*name == '[') {
		return (name_key_parse_cstring_unique (key, name));
    } else {
		return (name_key_parse_cstring_string (key, name));
    }
}

void
name_key_set_component(NameKeyP key, unsigned component,
					   NStringP string)
{
    ASSERT ((key->type == KT_UNIQUE) && (component < key->u.unique.length));
    nstring_assign (&(key->u.unique.components [component]), string);
}

NameKeyTypeT
name_key_type(NameKeyP key)
{
    return (key->type);
}

NStringP
name_key_string(NameKeyP key)
{
    ASSERT (key->type == KT_STRING);
    return (&(key->u.string));
}

unsigned
name_key_components(NameKeyP key)
{
    ASSERT (key->type == KT_UNIQUE);
    return (key->u.unique.length);
}

NStringP
name_key_get_component(NameKeyP key, unsigned component)
{
    ASSERT ((key->type == KT_UNIQUE) && (component < key->u.unique.length));
    return (&(key->u.unique.components [component]));
}

unsigned
name_key_hash_value(NameKeyP key)
{
#ifdef __TenDRA__
    unsigned hash_value; /* "tcc" complains if this is initialised */
#else
    unsigned hash_value = 0; /* "gcc" complains if this is not initialised */
#endif /* defined (__TenDRA__) */
    unsigned components;
    unsigned i;
	
    switch (key->type) EXHAUSTIVE {
	case KT_STRING:
		hash_value = nstring_hash_value (&(key->u.string));
		break;
	case KT_UNIQUE:
		components = key->u.unique.length;
		hash_value = components;
		for (i = 0; i < components; i ++) {
			hash_value += nstring_hash_value (&(key->u.unique.components [i]));
		}
		break;
    }
    return (hash_value);
}

BoolT
name_key_equal(NameKeyP key1, NameKeyP key2)
{
    unsigned components;
    unsigned i;
	
    if (key1->type != key2->type) {
		return (FALSE);
    }
    switch (key1->type) EXHAUSTIVE {
	case KT_STRING:
		return (nstring_equal (&(key1->u.string), &(key2->u.string)));
	case KT_UNIQUE:
		if ((components = key1->u.unique.length) != key2->u.unique.length) {
			return (FALSE);
		}
		for (i = 0; i < components; i ++) {
			if (!nstring_equal (&(key1->u.unique.components [i]),
								&(key2->u.unique.components [i]))) {
				return (FALSE);
			}
		}
		break;
    }
    return (TRUE);
}

void
name_key_assign(NameKeyP to, NameKeyP from)
{
    switch (to->type = from->type) EXHAUSTIVE {
	case KT_STRING:
		nstring_assign (&(to->u.string), &(from->u.string));
		break;
	case KT_UNIQUE:
		to->u.unique.length     = from->u.unique.length;
		to->u.unique.components = from->u.unique.components;
		break;
    }
}

void
name_key_copy(NameKeyP to, NameKeyP from)
{
    unsigned components;
    unsigned i;
	
    switch (to->type = from->type) EXHAUSTIVE {
	case KT_STRING:
		nstring_copy (&(to->u.string), &(from->u.string));
		break;
	case KT_UNIQUE:
		components = to->u.unique.length = from->u.unique.length;
		to->u.unique.components = ALLOCATE_VECTOR (NStringT, components);
		for (i = 0; i < components; i ++) {
			nstring_copy (&(to->u.unique.components [i]),
						  &(from->u.unique.components [i]));
		}
		break;
    }
}

void
name_key_destroy(NameKeyP key)
{
    unsigned components;
    unsigned i;
	
    switch (key->type) EXHAUSTIVE {
	case KT_STRING:
		nstring_destroy (&(key->u.string));
		break;
	case KT_UNIQUE:
		components = key->u.unique.length;
		for (i = 0; i < components; i ++) {
			nstring_destroy (&(key->u.unique.components [i]));
		}
		DEALLOCATE (key->u.unique.components);
		break;
    }
}

void
write_name_key(OStreamP ostream, NameKeyP key)
{
    char     sep = '[';
    unsigned components;
    unsigned i;
	
    switch (key->type) EXHAUSTIVE {
	case KT_STRING:
		write_name_key_1 (ostream, &(key->u.string));
		break;
	case KT_UNIQUE:
		components = key->u.unique.length;
		for (i = 0; i < components; i ++) {
			NStringP nstring = &(key->u.unique.components [i]);
			
			write_char (ostream, sep);
			write_name_key_1 (ostream, nstring);
			sep = '.';
		}
		write_char (ostream, ']');
		break;
    }
}

/*--------------------------------------------------------------------------*/

void
name_key_list_init(NameKeyListP list)
{
    list->head = NIL (NameKeyListEntryP);
}

void
name_key_list_add(NameKeyListP list, NameKeyP key)
{
    NameKeyListEntryP entry;
	
    for (entry = name_key_list_head (list); entry;
		 entry = name_key_list_entry_next (entry)) {
		if (name_key_equal (key, &(entry->key))) {
			name_key_destroy (key);
			return;
		}
    }
    entry       = ALLOCATE (NameKeyListEntryT);
    entry->next = list->head;
    name_key_assign (&(entry->key), key);
    list->head  = entry;
}

NameKeyListEntryP
name_key_list_head(NameKeyListP list)
{
    return (list->head);
}

NameKeyP
name_key_list_entry_key(NameKeyListEntryP entry)
{
    return (&(entry->key));
}

NameKeyListEntryP
name_key_list_entry_next(NameKeyListEntryP entry)
{
    return (entry->next);
}

/*--------------------------------------------------------------------------*/

void
name_key_pair_list_init(NameKeyPairListP list)
{
    list->head = NIL (NameKeyPairListEntryP);
}

BoolT
name_key_pair_list_add(NameKeyPairListP list,
					   NameKeyP from, NameKeyP to)
{
    NameKeyPairListEntryP entry;
	
    for (entry = name_key_pair_list_head (list); entry;
		 entry = name_key_pair_list_entry_next (entry)) {
		if (name_key_equal (from, &(entry->from))) {
			return (FALSE);
		}
    }
    entry       = ALLOCATE (NameKeyPairListEntryT);
    entry->next = list->head;
    name_key_assign (&(entry->from), from);
    name_key_assign (&(entry->to), to);
    list->head  = entry;
    return (TRUE);
}

NameKeyPairListEntryP
name_key_pair_list_head(NameKeyPairListP list)
{
    return (list->head);
}

NameKeyP
name_key_pair_list_entry_from(NameKeyPairListEntryP entry)
{
    return (&(entry->from));
}

NameKeyP
name_key_pair_list_entry_to(NameKeyPairListEntryP entry)
{
    return (&(entry->to));
}

NameKeyPairListEntryP
name_key_pair_list_entry_next(NameKeyPairListEntryP entry)
{
    return (entry->next);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
