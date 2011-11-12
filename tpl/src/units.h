/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/02/04 10:46:41 $
$Revision: 1.2 $
$Log: units.h,v $
 * Revision 1.2  1998/02/04  10:46:41  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/04  10:29:26  currie
 * tld units instead of tld2
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:42  currie
 * Added banner
 *
***********************************************************************/
#ifndef UNITS_INCLUDED
#define UNITS_INCLUDED

#include "streams.h"

#define tok_ent		0
#define tag_ent		1
#define al_tag_ent	2
#define NO_OF_ENTITIES	3

#define tld2_unit	0
#define version_unit	1
#define tokdec_unit	2
#define tokdef_unit	3
#define al_tagdef_unit	4
#define tagdec_unit	5
#define tagdef_unit	6
#define NO_OF_UNITS	7



typedef struct Link_struct {
	struct Link_struct *next;
	int unit_name;
	int capsule_name;
} Link;



typedef struct {
	TDF tdf;
	int no_labs;
	int no_entity[NO_OF_ENTITIES];
	Link *links[NO_OF_ENTITIES];
	int present;
} Unit;

typedef struct TDFlist_struct {
	TDF t;
	struct TDFlist_struct *next;
} TDFlist;

typedef struct {
	int unit_name;
	int unit_no;
} Name;

extern FILE *out_file;
extern int line_no_tok;
extern Unit units[NO_OF_UNITS];
extern int current_Unit;
extern int capsule_names[NO_OF_ENTITIES];
extern TDF lk_externs[NO_OF_ENTITIES];
extern char *ent_names[NO_OF_ENTITIES];
extern char *unit_names[NO_OF_UNITS];
extern Name *tokforintsh(Bool issigned);
extern Name *tokforlongsh(Bool issigned);
extern Name *tokforshortsh(Bool issigned);
extern Name *tokforcharsh(Bool issigned);
extern Name *tokforfloatsh(void);
extern Name *tokfordoublesh(void);
#define SELECT_UNIT(x)	current_TDF = &units[x].tdf; current_Unit = x;\
				      units[x].present = 1;
#define INIT_TDF(x)	(x)->first = (x)->last = create_chunk();\
				     (x)->no = 0; (x)->sort = 0;
#define SET_TDF(hold, x)	hold = current_TDF; INIT_TDF(x);\
				       current_TDF = x;
#define RESET_TDF(hold)	current_TDF = hold;
#define INC_LIST	current_TDF->no++

extern int next_label(void);
extern Name next_name(int ent);
extern int next_unit_name(int ent);
extern int next_capsule_name(int ent);
extern int capsule_name(Name *n, int ent);
extern int non_local(Name *n, int ent);
extern void make_tag(Name *n);
extern void make_tok(Name *n);
extern void make_al_tag(Name *n);
extern void make_unit(int unit_no);
extern long local_name(Name *n, int ent);
extern int cname_to_lname(int c_name, int ent);
extern void FILENAME(void);
extern void init_units(void);
extern void make_tdf_file(TDF *s, FILE *out_file);


#endif
