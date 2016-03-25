/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <exds/ostream.h>

#include "bnf-out-info.h"
#include "../output.h"

OutputInfoT *
bnf_out_info_info(BNFOutputInfoT *info)
{
	return info->info;
}

OStreamT *
bnf_out_info_ostream(BNFOutputInfoT *info)
{
	return out_info_get_current_ostream(info->info);
}

void
bnf_out_info_init(BNFOutputInfoT *info, OutputInfoT *out_info)
{
	info->info = out_info;
}

