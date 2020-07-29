/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
void		output_indent(OutputInfoT *, unsigned);

#endif /* !defined (H_OUTPUT) */
