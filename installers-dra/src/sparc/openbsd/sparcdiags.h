/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/solaris/sparcdiags.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: sparcdiags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1998/01/09  15:00:08  pwe
 * prep restructure
 *
 * Revision 1.2  1997/04/04  15:23:38  pwe
 * tidy re old DWARF interface
 *
 * Revision 1.1  1997/03/24  17:10:00  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.1.1.1  1995/03/13  10:18:55  john
 * Entered into CVS
 *
 * Revision 1.3  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.2  1994/07/04  08:35:54  djch
 * extra param to stabd
 *
 * Revision 1.1  1994/05/03  14:50:40  djch
 * Initial revision
 *
 * Revision 1.3  93/07/05  18:26:02  18:26:02  ra (Robert Andrews)
 * Include diag_fns.h for DWARF.
 *
 * Revision 1.2  93/06/29  14:31:11  14:31:11  ra (Robert Andrews)
 * Minor renaming of diagnostic routines.
 *
 * Revision 1.1  93/06/24  14:59:20  14:59:20  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef SPARCDDECS_INCLUDED
#define SPARCDDECS_INCLUDED

#include "config.h"

#include "dg_first.h"
#include "diaginfo.h"

#include "exptypes.h"
#include "installtypes.h"

#ifdef NEWDIAGS

extern void init_stab(void);
extern void init_stab_aux(void);
extern void code_diag_info(dg_info, void(*)(void *), void *);
extern void stab_global(dg_name, exp, char *, int);
extern void stab_proc(dg_name, exp, char *, int);
extern void stab_proc_end(void);
extern void stab_types(void);

#else

extern void init_stab(void);
extern void init_stab_aux(void);
extern void stab_collect_files(filename);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);
extern void stab_begin(diag_info *, int, exp);
extern void stab_end(diag_info *, exp);
extern void stab_file(long, bool);
extern void stab_global(diag_descriptor *, exp, char *, bool);
extern void stab_local(char *, diag_type, exp, long, long);
extern void stab_proc(diag_descriptor *, exp, char *, bool);
extern void stab_proc_end(void);
extern void stab_types(void);
extern void stabd(long, long, int);
extern long currentfile;

#endif

#endif /* SPARCDDECS_INCLUDED */
