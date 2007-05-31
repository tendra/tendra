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
 * c-out-info.h - Output control ADT.
 *
 * See the file "c-out-info.c" for more information.
 */

#ifndef H_C_OUT_INFO
#define H_C_OUT_INFO

#include "os-interface.h"
#include "dstring.h"
#include "ostream.h"
#include "output.h"

/*To avoid circularity:*/
struct CCodeT;

typedef enum {
    CPFX_TYPE,
    CPFX_FN,
    CPFX_IN,
    CPFX_OUT,
    CPFX_LABEL,
    CPFX_TERMINAL,
    CPFX_NUM_PREFIXES
} CPrefixT, *CPrefixP;

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

extern void		 c_out_info_init(COutputInfoP, OutputInfoP);
extern OutputInfoP	 c_out_info_info(COutputInfoP);
extern OStreamP		 c_out_info_ostream(COutputInfoP);
extern char *		 c_out_info_program_name(COutputInfoP);
extern char *		 c_out_info_source_name(COutputInfoP);
extern char *		 c_out_info_c_source_name(COutputInfoP);
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

#endif /* !defined (H_C_OUT_INFO) */
