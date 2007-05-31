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


/**** output.h --- Target independent output routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * See the file "output.c" for more information.
 *
 **** Change Log:
 * $Log: output.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:57:15  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:22  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_OUTPUT
#define H_OUTPUT

#include "os-interface.h"
#include "cstring.h"
#include "istream.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct OutputInfoT {
    char *			prog_name;
    OStreamP			current_ostream;
    IStreamP			istreams;
    OStreamP			ostreams;
    char *		       *input_names;
    char *		       *output_names;
    unsigned			tab_width;
} OutputInfoT, *OutputInfoP;

/*--------------------------------------------------------------------------*/

extern void		out_info_init(OutputInfoP, char *);
extern char *		out_info_get_prog_name(OutputInfoP);
extern void		out_info_set_current_ostream(OutputInfoP, unsigned);
extern OStreamP		out_info_get_current_ostream(OutputInfoP);
extern void		out_info_set_num_input_files(OutputInfoP, unsigned);
extern void		out_info_set_num_output_files(OutputInfoP, unsigned);
extern IStreamP		out_info_get_istream(OutputInfoP, unsigned);
extern OStreamP		out_info_get_ostream(OutputInfoP, unsigned);
extern void		out_info_set_infile_name(OutputInfoP, unsigned,
						 char *);
extern char *		out_info_get_infile_name(OutputInfoP, unsigned);
extern void		out_info_set_outfile_name(OutputInfoP, unsigned,
						  char *);
extern char *		out_info_get_outfile_name(OutputInfoP, unsigned);
extern void		out_info_set_tab_width(OutputInfoP, unsigned);
extern void		output_indent(OutputInfoP, unsigned);

#endif /* !defined (H_OUTPUT) */
