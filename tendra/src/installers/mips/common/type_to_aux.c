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
 *Revision 1.2  2002/11/21 22:31:10  nonce
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
 * Revision 1.2  1998/02/04  10:43:45  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:07  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/12  10:59:47  currie
 * gcc pedanttry
 *
 * Revision 1.2  1995/08/16  16:07:16  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 ***********************************************************************/
/*****************************************************************
 *
 *                           type_to_aux.c
 *
 *contains procedure
 *long add_type_to_aux (diag_type s, long ind)
 *which converts a TDF shape into an AUXU (see sym.h) and adds it to the auxillary table for the file number given as parameter as required by the MIPS symbol table.
 *If the entry generated is greater than 1 AUXU in length the index corresponding to the first entry made is returned.


********************************************************************/
#include "config.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <symconst.h>
#else
#include CROSS_INCLUDE/symconst.h>
#endif

#include "common_types.h"
#include "shapemacs.h"
#include "exp.h"
#include "expmacs.h"
#include "diagtypes.h"
#include "diag_fns.h"
#include "xalloc.h"
#include "symtab.h"
#include "new_symbol.h"
#include "basicread.h"
#include "mipsdiags.h"
#include "type_to_aux.h"

extern long mainfile;

int field=0;

long
set_tq(int qual, TIR *type, long ind)
{
    AUXU retaux;
    long index=0;
    switch (field++)	{
	case 0: break;
	case 1: type->tq1=type->tq0;
		break;
	case 2: type->tq2=type->tq1;
		type->tq1=type->tq0;
		break;
	case 3: type->tq3=type->tq2;
		type->tq2=type->tq1;
		type->tq1=type->tq0;
		break;
	case 4: type->tq4=type->tq3;
		type->tq3=type->tq2;
		type->tq2=type->tq1;
		type->tq1=type->tq0;
		break;
	case 5: type->tq5=type->tq4;
		type->tq4=type->tq3;
		type->tq3=type->tq2;
		type->tq2=type->tq1;
		type->tq1=type->tq0;
		break;
	case 6:	type->continued=1;
		retaux.ti=(*type);
		index=add_aux(retaux, ind);
		type=(TIR*)xcalloc(1,sizeof(TIR));
		type->tq0=qual;
		field=1;
		return index;
	}
    type->tq0=qual;
    return -1;
}

long
type_size(diag_type dt)
{
    switch (dt->key) {
	case DIAG_TYPE_VARIETY: {
		return shape_size(dt->data.var);
	}
	case DIAG_TYPE_STRUCT: case DIAG_TYPE_UNION: {
		return shape_size(dt->data.t_struct.tdf_shape);
	}
	case DIAG_TYPE_FLOAT: {
		return ((dt->data.f_var)?64:32);
	}
	case DIAG_TYPE_ARRAY: {
		long is = type_size(dt->data.array.element_type);
		return (is *(dt->data.array.upper_b-dt->data.array.lower_b+1));
	}
	case DIAG_TYPE_ENUM: {
		return type_size(dt->data.t_enum.base_type);
	}
	default: return 32;
    }
}

long
add_type_to_aux(diag_type dt, long ind)
{
    TIR* type=(TIR*)xcalloc(1,sizeof(TIR));
    long firstind= -1;
    int dimension=0;
    int elemsize=0;
    int scale=1;
    diag_type xdt = dt;
    AUXU maxaux, retaux;
    maxaux.isym=0xffffffff;
    field=0;
    if (dt == (diag_type)0) {
		return 1048575;
    }
	
    {type->bt=63;
	while (type->bt==63)
	{
        if (dt == (diag_type)0) {
			type->bt = btNil;
			retaux.ti=(*type);
			break;
		}
		switch (dt->key)
		{
		case DIAG_TYPE_BITFIELD: {
			type->bt=btUInt;
			type->fBitfield=1;
			retaux.ti = *type;
			firstind = add_aux(retaux, ind);
			retaux.rndx.rfd = dt->data.bitfield.no_of_bits.nat_val.small_nat;
			retaux.rndx.index=0;
			add_aux(retaux, ind);
			break;
        }
		case DIAG_TYPE_UNINIT:  case DIAG_TYPE_NULL: case DIAG_TYPE_INITED:
			type->bt = btNil;
			retaux.ti=(*type);
			break;
		case DIAG_TYPE_VARIETY: {
			switch (name(dt->data.var)) {
            case scharhd:
				type->bt = btChar;
				retaux.ti=(*type);
				break;
            case ucharhd:
				type->bt = btUChar;
				retaux.ti=(*type);
				break;
            case swordhd:
				type->bt = btShort;
				retaux.ti=(*type);
				break;
            case uwordhd:
				type->bt = btUShort;
				retaux.ti=(*type);
				break;
            case slonghd:
				type->bt = btInt;
				retaux.ti=(*type);
				break;
            case ulonghd:
				type->bt = btUInt;
				retaux.ti=(*type);
				break;
            default: failer("DIAGS - not variety ");
			}
			break;
        }
        case DIAG_TYPE_FLOAT: {
			if (dt->data.f_var == 0) {
				type->bt = btFloat;
			}
			else {
				type->bt = btDouble;
			}
			retaux.ti=(*type);
			break;
		}
			
		case DIAG_TYPE_PROC: {
			/* ???  MIPS   ???  should use result type ???  */
			set_tq(tqProc, type, ind);
			type->bt = btUInt;
			retaux.ti=(*type);
			break;
		}
		case DIAG_TYPE_PTR: {
			firstind= set_tq(tqPtr, type, ind);
			dt = dt->data.ptr.object;
			break;
		}
		case DIAG_TYPE_STRUCT: case DIAG_TYPE_UNION: {
			type->bt = (dt->key == DIAG_TYPE_STRUCT)? btStruct:btUnion;
			retaux.ti = *type;
			if (firstind==-1)
			{firstind=add_aux(retaux, ind);}
			else	{add_aux(retaux, ind);}
			retaux.rndx.rfd = mainfile;
			retaux.rndx.index=find_aux(dt);
			add_aux(retaux,ind);
			retaux.rndx.rfd = mainfile;
			retaux.rndx.index=0;
			break;
		}
		case DIAG_TYPE_ARRAY: {
			diag_type ndt = dt->data.array.element_type;
			firstind=set_tq(tqArray, type, ind);
			dimension=1;
			xdt = dt;
			
			while (ndt->key==DIAG_TYPE_ARRAY) {
				dimension++;
				ndt = ndt->data.array.element_type;
			}
			dt = ndt;
			elemsize = type_size(ndt)>>3;
			break;
		}
		case DIAG_TYPE_ENUM: case DIAG_TYPE_LOC: {
			dt= dt->data.t_enum.base_type;
			break;
		}
		default:
			failer ("bad diagnostics type");
			break;
		};
	}
	}
	
	
	if (firstind==-1)
	{firstind=add_aux(retaux,ind);
	}
	else
	{add_aux(retaux,ind);
	}
	
	while (dimension--) {
		int i;
		diag_type ndt = xdt;
		for (i=1;i<dimension;i++) {
			ndt = ndt->data.array.element_type;
		}
		i = no(ndt->data.array.upper_b) - no(ndt->data.array.lower_b)+1;
		retaux.rndx.rfd = 4095;
		retaux.rndx.index=4;
		add_aux(retaux,ind);
		retaux.rndx.rfd = mainfile;
		retaux.rndx.index=0;
		add_aux(retaux,ind);
		retaux.dnLow = no(ndt->data.array.lower_b);
		add_aux(retaux,ind);
		retaux.dnHigh = no(ndt->data.array.upper_b);
		add_aux(retaux,ind);
		retaux.width = elemsize*scale;
		scale =i*scale;
		add_aux(retaux,ind);
	}
	
    return firstind;
    /* return index of first element added to the AUX table */
}
