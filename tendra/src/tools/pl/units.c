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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:23  nonce
 *Remove ossg prototypes.  This commit is largely whitespace changes,
 *but is nonetheless important.  Here's why.
 *
 *I.  Background
 *=========================
 *
 *    The current TenDRA-4.1.2 source tree uses "ossg" prototype
 *conventions, based on the Open Systems Software Group publication "C
 *Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 *The goal behind ossg prototypes remains admirable: TenDRA should
 *support platforms that lack ANSI compliant compilers.  The explicit
 *nature of ossg's prototypes makes macro substition easy.
 *
 *    Here's an example of one function:
 *
 *    static void uop
 *	PROTO_N ( ( op, sha, a, dest, stack ) )
 *	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 *		  shape sha X exp a X where dest X ash stack )
 *    {
 *
 *tendra/src/installers/680x0/common/codec.c
 *
 *  The reasons for removing ossg are several, including:
 *
 *  0) Variables called 'X' present a problem (besides being a poor
 *variable name).
 *
 *  1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 *prototypes are easily handled by most every compiler these days.
 *
 *  2) Although TenDRA emphasizes portability, standards compliance is
 *the primary goal of the current project.  We should expect no less
 *from the compiler source code.
 *
 *  3) The benefits of complex prototypes are few, given parameter
 *promotion rules.  (Additionally, packing more types into int-sized
 *spaces tends to diminish type safety, and greatly complicates
 *debugging and testing.)
 *
 *  4) It would prove impractical to use an OSSG internal style document
 *in an open source project.
 *
 *  5) Quite frankly, ossg prototypes are difficult to read, but that's
 *certainly a matter of taste and conditioning.
 *
 *II.  Changes
 *=========================
 *
 *   This commit touches most every .h and .c file in the tendra source
 *tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 *was used to automate the following changes:
 *
 *   A.  Prototype Conversions.
 *   --------------------------------------------------
 *
 *   The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 *rewritten to ISO-compliant form.  Not every file was touched.  The
 *files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 *left for hand editing.  These files provide header generation, or have
 *non-ossg compliant headers to start with.  Scripting around these
 *would take too much time; a separate hand edit will fix them.
 *
 *   B.  Statement Spacing
 *   --------------------------------------------------
 *
 *   Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 *parenthetical lexemes.  (See the quoted example above.)  A simple
 *text substitution was made for:
 *
 *     Before            After
 *===================================
 *
 *   if ( x )            if (x)
 *   if(x)               if (x)
 *   x = 5 ;             x = 5;
 *   ... x) )            ... x))
 *
 *All of these changes are suggested by style(9).  Additional, statement
 *spacing considerations were made for all of the style(9) keywords:
 *"if" "while" "for" "return" "switch".
 *
 *A few files seem to have too few spaces around operators, e.g.:
 *
 *      arg1*arg2
 *
 *instead of
 *
 *      arg1 * arg2
 *
 *These were left for hand edits and later commits, since few files
 *needed these changes.  (At present, the rmossg.el script takes 1 hour
 *to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 *needed change would take too much time.)
 *
 *   C.  License Information
 *   --------------------------------------------------
 *
 *After useful discussion on IRC, the following license changes were
 *made:
 *
 *   1) Absent support for $License::BSD$ in the repository, license
 *and copyright information was added to each file.
 *
 *   2) Each file begins with:
 *
 *   Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *   All rights reserved.
 *
 *   Usually, copyright stays with the author of the code; however, I
 *feel very strongly that this is a group effort, and so the tendra
 *project should claim any new (c) interest.
 *
 *   3) The comment field then shows the bsd license and warranty
 *
 *   4) The comment field then shows the Crown Copyright, since our
 *changes are not yet extensive enough to claim any different.
 *
 *   5) The comment field then closes with the $TenDRA$ tag.
 *
 *   D.  Comment Formatting
 *   --------------------------------------------------
 *
 *The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *    /*
 *       Statement statement
 *       statement
 *     */
 *
 *while style(9) suggests:
 *
 *    /*
 *     * Statement statement
 *     * statement
 *     */
 *
 *Not every comment in -4.1.2 needed changing.  A parser was written to
 *identify non-compliant comments.  Note that a few comments do not
 *follow either the TenDRA-4.1.2 style or style(9), or any style I can
 *recognize.  These need hand fixing.
 *
 *   E.  Indentation
 *   --------------------------------------------------
 *
 *   A elisp tendra-c-mode was created to define how code should be
 *indented.  The structure follows style(9) in the following regards:
 *
 *  (c-set-offset 'substatement-open 0)
 *  (setq c-indent-tabs-mode t
 *	c-indent-level 4
 *	c-argdecl-indent t
 *	c-tab-always-indent t
 *	backward-delete-function nil
 *	c-basic-offset 4
 *	tab-width 4))
 *
 *This means that substatement opening are not indented.  E.g.:
 *
 *   if (condition)
 *   {
 *
 *instead of
 *
 *   if (condition)
 *     {
 *
 *or even
 *
 *   if (condition) {
 *
 *Each statement is indented by a tab instead of a spaces.  Set your tab
 *stop to comply with style(9); see the vim resources in the tendra
 *tree.  I'll add the emacs mode support shortly.
 *
 *No doubt, a function or two escaped change because of unusual
 *circumstances.  These must be hand fixed as well.
 *
 *III.  Things Not Changed
 *=========================
 *
 *    A large number of style(9) deficiencies remain.  These will
 *require a separate effort.  I decided to stop with the changes noted
 *above because:
 *
 *   0)  The script currently takes hours to run to completion even on
 *high-end consumer machines.
 *
 *   1)  We need to move on and fix other substantive problems.
 *
 *   2) The goal of this commit was *just* ossg removal; I took the
 *opportunity to get other major white-space issues out of the way.
 *
 *    I'll also note that despite this commit, a few ossg issues remain.
 *These include:
 *
 *   0) The ossg headers remain.  They contain useful flags needed by
 *other operations.  Additionally, the BUILD_ERRORS perl script still
 *generates ossg-compliant headers.  (This is being removed as we change
 *the build process.)
 *
 *   1) A few patches of code check for ossg flags: "if (ossg) etc."
 *These can be hand removed as well.
 *
 *   2) No doubt, a few ossg headers escaped the elisp script.  We can
 *address these seriatim.
 *
 *IV.  Testing
 *=========================
 *
 *    Without a complete build or test suite, it's difficult to
 *determine if these changes have introduced any bugs.  I've identified
 *several situations where removal of ossg caused bugs in sid and
 *calculus operations.  The elisp script avoids these situations; we
 *will hand edit a few files.
 *
 *    As is, the changes should behave properly; the source base builds
 *the same before and after the rmossg.el script is run.  Nonetheless,
 *please note that this commit changes over 23,000 PROTO declarations,
 *and countless line changes.  I'll work closely with any developers
 *affected by this change.
 *
 * Revision 1.2  1998/02/04  10:46:41  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/05  16:27:54  currie
 * include files + 2r lex
 *
 * Revision 1.3  1995/09/04  10:29:24  currie
 * tld units instead of tld2
 *
 * Revision 1.2  1995/08/21  16:00:59  currie
 * put <stdlib> at top of headers
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:40  currie
 * Added banner
 *
 ***********************************************************************/
#include "config.h"
#include "util.h"
#include "readstreams.h"
#include "streams.h"
#include "units.h"
#include "encodings.h"
#include "enc_nos.h"
#include "includes.h"
#include "errors.h"
#include "defs.h"
#include "syntax.h"


FILE *out_file;
Unit units[NO_OF_UNITS];
int current_Unit;
int capsule_names[NO_OF_ENTITIES];
TDF lk_externs[NO_OF_ENTITIES];
char * ent_names[NO_OF_ENTITIES] = {"token","tag","alignment"};
char * unit_names[NO_OF_UNITS] =
{"tld", "versions", "tokdec", "tokdef", "aldef", "tagdec",
 "tagdef"};

int line_no_tok = -1;


int
next_label()
{
	return (units[current_Unit].no_labs++);
}


int
next_unit_name(int ent)
{
	return ((units[current_Unit].no_entity)[ent]++);
}


Name
next_name(int ent)
{
	Name ans;
	ans.unit_no = current_Unit;
	ans.unit_name = next_unit_name(ent);
	return ans;
}


int
next_capsule_name(int ent)
{
	return (capsule_names[ent]++);
}


int
capsule_name(Name * n, int ent)
{
	Unit * nl_unit = & units[n->unit_no];
	Link * nl_links = (nl_unit->links)[ent];
	while (nl_links != (Link*)0) {
		if (n->unit_name == nl_links->unit_name)
			return nl_links->capsule_name;
		nl_links = nl_links->next;
	}
	Assert(n->unit_name < (nl_unit->no_entity)[ent]);
	nl_links = MALLOC(Link);
	nl_links->capsule_name = next_capsule_name(ent);
	nl_links->unit_name = n->unit_name;
	nl_links->next = (nl_unit->links)[ent];
	(nl_unit->links)[ent] = nl_links;
	return nl_links->capsule_name;
}


int
cname_to_lname(int c_name, int ent)
{
	Link * links = (units[current_Unit].links)[ent];
	while (links != (Link*)0) {
		if (c_name == links->capsule_name) return links->unit_name;
		links = links->next;
	}
	links = MALLOC(Link);
	links->capsule_name = c_name;
	links->unit_name = next_unit_name(ent);
	links->next = (units[current_Unit].links)[ent];
	(units[current_Unit].links)[ent] = links;
	return links->unit_name;
}


int
non_local(Name * n, int ent)
{
	return cname_to_lname(capsule_name(n, ent),ent);
}


void
make_tag(Name * n)
{
  	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
		non_local(n, tag_ent);
	Assert(loc_name<(units[current_Unit].no_entity)[tag_ent]);
	o_make_tag(out_tdfint32(UL(loc_name)));
}


void
make_tok(Name * n)
{
  	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
		non_local(n, tok_ent);
	Assert(loc_name<(units[current_Unit].no_entity)[tok_ent]);
	o_make_tok(out_tdfint32(UL(loc_name)));
}


void
make_al_tag(Name * n)
{
  	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
		non_local(n, al_tag_ent);
	Assert(loc_name<(units[current_Unit].no_entity)[al_tag_ent]);
	o_make_al_tag(out_tdfint32(UL(loc_name)));
}


long
local_name(Name * n, int ent)
{
	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
		non_local(n, ent);
	Assert(loc_name<(units[current_Unit].no_entity)[ent]);
	return loc_name;
}


void
FILENAME()
{
	o_make_filename(
		o_make_nat(out_tdfint32(UL(0))),
		out_tdfstring_bytes("?",8,1),
		out_tdfstring_bytes(file_name, 8, UI(strlen(file_name)))
		);
}


void
init_units()
{
	int i,j;
	if (MAJOR_NO == 4 && MINOR_NO == 1) {
		MINOR_NO = 0;
	}
	for (i=0; i<NO_OF_UNITS; i++) {
		Unit * u = & units[i];
		INIT_TDF(&u->tdf);
		u->no_labs = 0;
		u->present = (i==version_unit || i == tld2_unit);
		for (j=0; j<NO_OF_ENTITIES; j++) {
			(u->no_entity)[j] = 0;
			(u->links)[j] = (Link*)0;
		}
	}
}


static void
make_links(Link * l)
{
	o_make_links(
	{ while (l!=(Link*)0) {
	   	LIST_ELEM(
			o_make_link(out_tdfint32(UL(l->unit_name)),
						out_tdfint32(UL(l->capsule_name))
				)
			);
	   	l = l->next;
	}
	}
		);
}


static void
props(int unit_no)
{
	Unit * u = units+unit_no;
	TDF temp;
	NEW_STREAM (&temp,
				switch (unit_no) {
				case version_unit:
					o_make_versions(
					{ LIST_ELEM(o_make_version(out_tdfint32(MAJOR_NO),
											   out_tdfint32(MINOR_NO)
									)
						);
					}
						);
					break;
				case tokdec_unit:
					o_make_tokdecs({ append_TDF(&u->tdf, 1);
					current_TDF->no = u->tdf.no;
					}
						);
					break;
				case tokdef_unit:
					o_make_tokdefs(out_tdfint32(UL(u->no_labs)),
					{ append_TDF(&u->tdf, 1);
					current_TDF->no = u->tdf.no;
					}
						);
					break;
				case tagdec_unit:
					o_make_tagdecs(out_tdfint32(UL(u->no_labs)),
					{ append_TDF(&u->tdf, 1);
					current_TDF->no = u->tdf.no;
					}
						);
					break;
				case tagdef_unit:
					o_make_tagdefs(out_tdfint32(UL(u->no_labs)),
					{ append_TDF(&u->tdf, 1);
					current_TDF->no = u->tdf.no;
					}
						);
					break;
				case al_tagdef_unit:
					o_make_al_tagdefs(out_tdfint32(UL(u->no_labs)),
					{ append_TDF(&u->tdf, 1);
					current_TDF->no = u->tdf.no;
					}
						);
					break;
				default: fail("Don't know unit type");
				}
		);
	append_bytestream(&temp,1);
}


void
make_unit(int unit_no)
{
	Unit * u = units+unit_no;
	int i;
	o_make_unit(
		if (unit_no != tld2_unit)
	{ for (i=0; i<NO_OF_ENTITIES; i++) {
	   	LIST_ELEM(out_tdfint32(UL(u->no_entity[i])));
	}
	},
		if (unit_no != tld2_unit)
	{ for (i=0; i<NO_OF_ENTITIES; i++) {
	   	LIST_ELEM(make_links(u->links[i]));
	}
	},
		if (unit_no != tld2_unit)
	{ props(unit_no); }
		else { append_bytestream(&u->tdf, 1);	}
		);
}


static int
get_byte()
{
	unsigned int x=0;
	int i;
	for (i=7; i>=0; i--) {
		unsigned int y = get_bit();
		if (y>1) return -1;
		x+= (y<<i);
	}
	return (int)x;
}


void
make_tdf_file(TDF * s, FILE * file)
{
  	Instream ins;
  	Chunk * ch = s->first;
  	int offst = 0;
  	int x;
	curin = &ins;
	curin->ch = ch;
	curin->byte_pos = 0;
	curin->bit_pos = 0;
	
	while (ch != (Chunk*)0)	{
		offst += ch->offst;
		offst &= 7;
		if (ch->next == (Chunk*)0 || ch->next->aligned) {
			if (offst !=0) {
				ch->offst += (unsigned char)(8-offst);
				if (ch->offst >= 8) { ch->usage+=1; ch->offst-=8; }
				offst=0;
			}
		}
		ch = ch->next;
	}
	
	while ((x = get_byte())>=0) {
		IGNORE fputc(x, file);
	}
}
