/*
 * Copyright (c) 2002, 2003, 2004 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * This code is derived from software contributed to The TenDRA Project by
 * Jeroen Ruigrok van der Werven.
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


/*** c-out-info.h --- Output control ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-out-info.c" for more information.
 *
 *** Change Log:
 * $Log: c-out-info.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/03/01  09:53:15  smf
 * c-code.c, c-out-info.c, c-out-info.h, c-output.c:
 * 	- improved unreachable code analysis;
 * 	- improved some output formatting;
 * 	- added support for comment or macro to mark unreachable code.
 *
 * Revision 1.2  1994/12/15  09:56:29  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:18  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_C_OUT_INFO
#define H_C_OUT_INFO

#include "os-interface.h"
#include "dstring.h"
#include "ostream.h"
#include "output.h"

/*To avoid circularity:*/
struct CCodeT;

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int CPrefixT, *CPrefixP;
#define CPFX_TYPE		(0)
#define CPFX_FN			(1)
#define CPFX_IN			(2)
#define CPFX_OUT		(3)
#define CPFX_LABEL		(4)
#define CPFX_TERMINAL		(5)
#define CPFX_NUM_PREFIXES	(6)
#else
typedef enum {
    CPFX_TYPE,
    CPFX_FN,
    CPFX_IN,
    CPFX_OUT,
    CPFX_LABEL,
    CPFX_TERMINAL,
    CPFX_NUM_PREFIXES
} CPrefixT, *CPrefixP;
#endif /* defined (FS_NO_ENUM) */

typedef struct COutputInfoT {
    OutputInfoP		info;
    struct CCodeT      *header1;
    struct CCodeT      *header2;
    struct CCodeT      *trailer1;
    struct CCodeT      *trailer2;
    NStringT		prefixes[CPFX_NUM_PREFIXES];
    BoolT		prototypes;
    BoolT		numeric_ids;
    BoolT		casts;
    BoolT		unreachable;
    BoolT		lines;
    unsigned		split;
} COutputInfoT, *COutputInfoP;

/*--------------------------------------------------------------------------*/

extern void		 c_out_info_init(COutputInfoP, OutputInfoP);
extern OutputInfoP	 c_out_info_info(COutputInfoP);
extern OStreamP		 c_out_info_ostream(COutputInfoP);
extern CStringP		 c_out_info_program_name(COutputInfoP);
extern CStringP		 c_out_info_source_name(COutputInfoP);
extern CStringP		 c_out_info_c_source_name(COutputInfoP);
extern struct CCodeT	*c_out_info_get_header1(COutputInfoP);
extern void		 c_out_info_set_header1(COutputInfoP, struct CCodeT *);
extern struct CCodeT	*c_out_info_get_header2(COutputInfoP);
extern void		 c_out_info_set_header2(COutputInfoP, struct CCodeT *);
extern struct CCodeT	*c_out_info_get_trailer1(COutputInfoP);
extern void		 c_out_info_set_trailer1(COutputInfoP, struct CCodeT *);
extern struct CCodeT	*c_out_info_get_trailer2(COutputInfoP);
extern void		 c_out_info_set_trailer2(COutputInfoP, struct CCodeT *);
extern NStringP		 c_out_info_type_prefix(COutputInfoP);
extern NStringP		 c_out_info_fn_prefix(COutputInfoP);
extern NStringP		 c_out_info_in_prefix(COutputInfoP);
extern NStringP		 c_out_info_out_prefix(COutputInfoP);
extern NStringP		 c_out_info_label_prefix(COutputInfoP);
extern NStringP		 c_out_info_terminal_prefix(COutputInfoP);
extern NStringP		 c_out_info_prefix(COutputInfoP, CPrefixT);
extern BoolT		 c_out_info_get_prototypes(COutputInfoP);
extern void		 c_out_info_set_prototypes(COutputInfoP, BoolT);
extern BoolT		 c_out_info_get_numeric_ids(COutputInfoP);
extern void		 c_out_info_set_numeric_ids(COutputInfoP, BoolT);
extern BoolT		 c_out_info_get_casts(COutputInfoP);
extern void		 c_out_info_set_casts(COutputInfoP, BoolT);
extern BoolT		 c_out_info_get_unreachable(COutputInfoP);
extern void		 c_out_info_set_unreachable(COutputInfoP, BoolT);
extern BoolT		 c_out_info_get_lines(COutputInfoP);
extern void		 c_out_info_set_lines(COutputInfoP, BoolT);
extern unsigned		 c_out_info_get_split(COutputInfoP);
extern void		 c_out_info_set_split(COutputInfoP, unsigned);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define c_out_info_info(o)	((o)->info)
#define c_out_info_ostream(o)	(out_info_get_current_ostream((o)->info))
#define c_out_info_program_name(o)	(out_info_get_prog_name((o)->info))
#define c_out_info_source_name(o)\
(out_info_get_infile_name((o)->info, (unsigned)0))
#define c_out_info_c_source_name(o)\
(out_info_get_infile_name((o)->info, (unsigned)1))
#define c_out_info_get_header1(o)	((o)->header1)
#define c_out_info_set_header1(o, c)	((o)->header1 = (c))
#define c_out_info_get_header2(o)	((o)->header2)
#define c_out_info_set_header2(o, c)	((o)->header2 = (c))
#define c_out_info_get_trailer1(o)	((o)->trailer1)
#define c_out_info_set_trailer1(o, c)	((o)->trailer1 = (c))
#define c_out_info_get_trailer2(o)	((o)->trailer2)
#define c_out_info_set_trailer2(o, c)	((o)->trailer2 = (c))
#define c_out_info_type_prefix(o)	(&((o)->prefixes[CPFX_TYPE]))
#define c_out_info_fn_prefix(o)		(&((o)->prefixes[CPFX_FN]))
#define c_out_info_in_prefix(o)		(&((o)->prefixes[CPFX_IN]))
#define c_out_info_out_prefix(o)	(&((o)->prefixes[CPFX_OUT]))
#define c_out_info_label_prefix(o)	(&((o)->prefixes[CPFX_LABEL]))
#define c_out_info_terminal_prefix(o)	(&((o)->prefixes[CPFX_TERMINAL]))
#define c_out_info_prefix(o, i)		(&((o)->prefixes[(i)]))
#define c_out_info_get_prototypes(o)	((o)->prototypes)
#define c_out_info_set_prototypes(o, b)	((o)->prototypes = (b))
#define c_out_info_get_numeric_ids(o)	((o)->numeric_ids)
#define c_out_info_set_numeric_ids(o, b)	((o)->numeric_ids = (b))
#define c_out_info_get_casts(o)		((o)->casts)
#define c_out_info_set_casts(o, b)	((o)->casts = (b))
#define c_out_info_get_unreachable(o)	((o)->unreachable)
#define c_out_info_set_unreachable(o, b)	((o)->unreachable = (b))
#define c_out_info_get_lines(o)		((o)->lines)
#define c_out_info_set_lines(o, b)	((o)->lines = (b))
#define c_out_info_get_split(o)		((o)->split)
#define c_out_info_set_split(o, n)	((o)->split = (n))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_C_OUT_INFO) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
