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
    CStringP			prog_name;
    OStreamP			current_ostream;
    IStreamP			istreams;
    OStreamP			ostreams;
    CStringP		       *input_names;
    CStringP		       *output_names;
    unsigned			tab_width;
} OutputInfoT, *OutputInfoP;

/*--------------------------------------------------------------------------*/

extern void			out_info_init
	PROTO_S ((OutputInfoP, CStringP));
extern CStringP			out_info_get_prog_name
	PROTO_S ((OutputInfoP));
extern void			out_info_set_current_ostream
	PROTO_S ((OutputInfoP, unsigned));
extern OStreamP			out_info_get_current_ostream
	PROTO_S ((OutputInfoP));
extern void			out_info_set_num_input_files
	PROTO_S ((OutputInfoP, unsigned));
extern void			out_info_set_num_output_files
	PROTO_S ((OutputInfoP, unsigned));
extern IStreamP			out_info_get_istream
	PROTO_S ((OutputInfoP, unsigned));
extern OStreamP			out_info_get_ostream
	PROTO_S ((OutputInfoP, unsigned));
extern void			out_info_set_infile_name
	PROTO_S ((OutputInfoP, unsigned, CStringP));
extern CStringP			out_info_get_infile_name
	PROTO_S ((OutputInfoP, unsigned));
extern void			out_info_set_outfile_name
	PROTO_S ((OutputInfoP, unsigned, CStringP));
extern CStringP			out_info_get_outfile_name
	PROTO_S ((OutputInfoP, unsigned));
extern void			out_info_set_tab_width
	PROTO_S ((OutputInfoP, unsigned));
extern void			output_indent
	PROTO_S ((OutputInfoP, unsigned));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define out_info_get_prog_name(o) ((o)->prog_name)
#define out_info_get_current_ostream(o) ((o)->current_ostream)
#define out_info_get_istream(o, i) (&((o)->istreams [(i)]))
#define out_info_get_ostream(o, i) (&((o)->ostreams [(i)]))
#define out_info_set_infile_name(o, i, s) ((o)->input_names [(i)] = (s))
#define out_info_get_infile_name(o, i) ((o)->input_names [(i)])
#define out_info_set_outfile_name(o, i, s) ((o)->output_names [(i)] = (s))
#define out_info_get_outfile_name(o, i) ((o)->output_names [(i)])
#define out_info_set_tab_width(o, w) ((o)->tab_width = (w))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_OUTPUT) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../generated")
 * end:
**/
