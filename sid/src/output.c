/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * output.c - Target independent output routines.
 *
 * This file implements some generic output routines.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/istream.h>

#include "output.h"

void
out_info_init(OutputInfoT *info, char *prog)
{
	info->prog_name       = prog;
	info->current_ostream = NULL;
	info->istreams        = NULL;
	info->ostreams        = NULL;
	info->input_names     = NULL;
	info->output_names    = NULL;
}

char *
out_info_get_prog_name(OutputInfoT *info)
{
	return info->prog_name;
}

void
out_info_set_current_ostream(OutputInfoT *info, unsigned i)
{
	info->current_ostream = &info->ostreams[i];
}

OStreamT *
out_info_get_current_ostream(OutputInfoT *info)
{
	return info->current_ostream;
}

void
out_info_set_num_input_files(OutputInfoT *info, unsigned size)
{
	info->istreams    = ALLOCATE_VECTOR(IStreamT, size);
	info->input_names = ALLOCATE_VECTOR(char *, size);
}

void
out_info_set_num_output_files(OutputInfoT *info, unsigned size)
{
	info->ostreams     = ALLOCATE_VECTOR(OStreamT, size);
	info->output_names = ALLOCATE_VECTOR(char *, size);
}

IStreamT *
out_info_get_istream(OutputInfoT *info, unsigned i)
{
	return &info->istreams[i];
}

OStreamT *
out_info_get_ostream(OutputInfoT *info, unsigned i)
{
	return &info->ostreams[i];
}

void
out_info_set_infile_name(OutputInfoT *info, unsigned i, char *name)
{
	info->input_names[i] = name;
}

char *
out_info_get_infile_name(OutputInfoT *info, unsigned i)
{
	return info->input_names[i];
}

void
out_info_set_outfile_name(OutputInfoT *info, unsigned i, char *name)
{
	info->output_names[i] = name;
}

char *
out_info_get_outfile_name(OutputInfoT *info, unsigned i)
{
	return info->output_names[i];
}

void
output_indent(OutputInfoT *info, unsigned indent)
{
	OStreamT *ostream   = out_info_get_current_ostream(info);

	while (indent--) {
		write_tab(ostream);
	}
}
