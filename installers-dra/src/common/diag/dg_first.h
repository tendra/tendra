/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: dg_first.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1998/01/11  18:44:50  pwe
 * consistent new/old diags
 *
 * Revision 1.1  1997/08/23  13:26:43  pwe
 * initial ANDF-DE
 *
***********************************************************************/
#ifndef dg_first_key
#define dg_first_key

/* breaks type cycles */

#include "config.h"


typedef struct dg_name_t *dg_name;
typedef struct dg_type_t *dg_type;
typedef struct dg_info_t *dg_info;
typedef struct file_t *dg_filename;

#ifdef NEWDIAGS
typedef struct dg_info_t diag_info;
typedef struct dg_name_t diag_global;
#endif

#endif
