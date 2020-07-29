/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef H_BNF_OUT_INFO
#define H_BNF_OUT_INFO

#include <exds/ostream.h>

#include "../output.h"

typedef struct BNFOutputInfoT {
	OutputInfoT *info;
} BNFOutputInfoT;

OutputInfoT *bnf_out_info_info(BNFOutputInfoT *info);
OStreamT *bnf_out_info_ostream(BNFOutputInfoT *info);
void bnf_out_info_init(BNFOutputInfoT *, OutputInfoT *);

#endif /* !defined (H_BNF_OUT_INFO) */

