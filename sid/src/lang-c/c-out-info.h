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

#include "../os-interface.h"
#include "../eds/dstring.h"
#include "../eds/ostream.h"
#include "../output.h"

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
} CPrefixT;

typedef struct COutputInfoT {
    OutputInfoT *		info;
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
} COutputInfoT;

extern void		 c_out_info_init(COutputInfoT *, OutputInfoT *);
extern OutputInfoT *	 c_out_info_info(COutputInfoT *);
extern OStreamT *		 c_out_info_ostream(COutputInfoT *);
extern char *		 c_out_info_program_name(COutputInfoT *);
extern char *		 c_out_info_source_name(COutputInfoT *);
extern char *		 c_out_info_c_source_name(COutputInfoT *);
extern struct CCodeT	*c_out_info_get_header1(COutputInfoT *);
extern void		 c_out_info_set_header1(COutputInfoT *, struct CCodeT *);
extern struct CCodeT	*c_out_info_get_header2(COutputInfoT *);
extern void		 c_out_info_set_header2(COutputInfoT *, struct CCodeT *);
extern struct CCodeT	*c_out_info_get_trailer1(COutputInfoT *);
extern void		 c_out_info_set_trailer1(COutputInfoT *, struct CCodeT *);
extern struct CCodeT	*c_out_info_get_trailer2(COutputInfoT *);
extern void		 c_out_info_set_trailer2(COutputInfoT *, struct CCodeT *);
extern NStringT *		 c_out_info_type_prefix(COutputInfoT *);
extern NStringT *		 c_out_info_fn_prefix(COutputInfoT *);
extern NStringT *		 c_out_info_in_prefix(COutputInfoT *);
extern NStringT *		 c_out_info_out_prefix(COutputInfoT *);
extern NStringT *		 c_out_info_label_prefix(COutputInfoT *);
extern NStringT *		 c_out_info_terminal_prefix(COutputInfoT *);
extern NStringT *		 c_out_info_prefix(COutputInfoT *, CPrefixT);
extern BoolT		 c_out_info_get_prototypes(COutputInfoT *);
extern void		 c_out_info_set_prototypes(COutputInfoT *, BoolT);
extern BoolT		 c_out_info_get_numeric_ids(COutputInfoT *);
extern void		 c_out_info_set_numeric_ids(COutputInfoT *, BoolT);
extern BoolT		 c_out_info_get_casts(COutputInfoT *);
extern void		 c_out_info_set_casts(COutputInfoT *, BoolT);
extern BoolT		 c_out_info_get_unreachable(COutputInfoT *);
extern void		 c_out_info_set_unreachable(COutputInfoT *, BoolT);
extern BoolT		 c_out_info_get_lines(COutputInfoT *);
extern void		 c_out_info_set_lines(COutputInfoT *, BoolT);
extern unsigned		 c_out_info_get_split(COutputInfoT *);
extern void		 c_out_info_set_split(COutputInfoT *, unsigned);

#endif /* !defined (H_C_OUT_INFO) */
