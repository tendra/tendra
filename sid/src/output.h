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
 * output.h - Target independent output routines.
 *
 * See the file "output.c" for more information.
 */

#ifndef H_OUTPUT
#define H_OUTPUT

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/istream.h>
#include <exds/ostream.h>

typedef struct OutputInfoT {
    char *			prog_name;
    OStreamT *			current_ostream;
    IStreamT *			istreams;
    OStreamT *			ostreams;
    char *		       *input_names;
    char *		       *output_names;
    unsigned			tab_width;
} OutputInfoT;

void		out_info_init(OutputInfoT *, char *);
char *		out_info_get_prog_name(OutputInfoT *);
void		out_info_set_current_ostream(OutputInfoT *, unsigned);
OStreamT *		out_info_get_current_ostream(OutputInfoT *);
void		out_info_set_num_input_files(OutputInfoT *, unsigned);
void		out_info_set_num_output_files(OutputInfoT *, unsigned);
IStreamT *		out_info_get_istream(OutputInfoT *, unsigned);
OStreamT *		out_info_get_ostream(OutputInfoT *, unsigned);
void		out_info_set_infile_name(OutputInfoT *, unsigned,
						 char *);
char *		out_info_get_infile_name(OutputInfoT *, unsigned);
void		out_info_set_outfile_name(OutputInfoT *, unsigned,
						  char *);
char *		out_info_get_outfile_name(OutputInfoT *, unsigned);
void		out_info_set_tab_width(OutputInfoT *, unsigned);
void		output_indent(OutputInfoT *, unsigned);

#endif /* !defined (H_OUTPUT) */
