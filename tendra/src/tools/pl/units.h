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

#define NO_OF_ENTITIES 3
#define tag_ent 1
#define tok_ent 0
#define al_tag_ent 2

#define NO_OF_UNITS 7
#define tld2_unit 0
#define version_unit 1
#define tokdec_unit 2
#define tokdef_unit 3
#define al_tagdef_unit 4
#define tagdec_unit 5
#define tagdef_unit 6



typedef struct Link_struct{
		struct Link_struct * next;
		int unit_name;
		int capsule_name;
	} Link;



typedef struct{ TDF tdf; 
		int no_labs;
		int no_entity[NO_OF_ENTITIES];
		Link * links[NO_OF_ENTITIES];
		int present; 
	      } Unit;
	      
typedef struct TDFlist_struct{ TDF t; struct TDFlist_struct * next;}
		TDFlist;

typedef struct{ int unit_name; int unit_no; } Name;

extern FILE *out_file ;
extern int line_no_tok;
extern Unit units[NO_OF_UNITS];
extern int current_Unit;
extern int capsule_names[NO_OF_ENTITIES];
extern TDF lk_externs[NO_OF_ENTITIES];
extern char * ent_names[NO_OF_ENTITIES];
extern char * unit_names[NO_OF_UNITS];
extern Name * tokforintsh PROTO_S((Bool issigned));
extern Name * tokforlongsh PROTO_S((Bool issigned));
extern Name * tokforshortsh PROTO_S((Bool issigned));
extern Name * tokforcharsh PROTO_S((Bool issigned));
extern Name * tokforfloatsh PROTO_S((void));
extern Name * tokfordoublesh PROTO_S((void));
#define SELECT_UNIT(x) current_TDF = &units[x].tdf; current_Unit = x;\
			units[x].present = 1;
#define INIT_TDF(x) (x)->first = (x)->last = create_chunk();\
		    (x)->no = 0; (x)->sort = 0;
#define SET_TDF(hold, x) hold = current_TDF; INIT_TDF(x); current_TDF = x;
#define RESET_TDF(hold) current_TDF = hold;
#define INC_LIST current_TDF->no++

extern int next_label PROTO_S((void));
extern Name next_name PROTO_S((int ent));
extern int next_unit_name PROTO_S((int ent));
extern int next_capsule_name PROTO_S((int ent));
extern int capsule_name PROTO_S((Name * n, int ent));
extern int non_local PROTO_S((Name * n, int ent));
extern void make_tag PROTO_S((Name * n));
extern void make_tok PROTO_S((Name * n));
extern void make_al_tag PROTO_S((Name * n));
extern void make_unit PROTO_S((int unit_no));
extern long local_name PROTO_S((Name * n, int ent));
extern int cname_to_lname PROTO_S((int c_name, int ent));
extern void FILENAME PROTO_S((void));
extern void init_units PROTO_S((void));
extern void make_tdf_file PROTO_S((TDF * s, FILE * out_file));


#endif
