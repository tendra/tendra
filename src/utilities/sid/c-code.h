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


/*** c-code.h --- SID C code stuff.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-code.c" for details.
 *
 *** Change Log:
 * $Log: c-code.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:25  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:17  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_C_CODE
#define H_C_CODE

#include "os-interface.h"
#include "c-out-info.h"
#include "cstring.h"
#include "dalloc.h"
#include "dstring.h"
#include "entry.h"
#include "rstack.h"
#include "rule.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int CCodeItemTypeT, *CCodeItemTypeP;
#define CCT_STRING	(0)
#define CCT_LABEL	(1)
#define CCT_IDENT	(2)
#define CCT_MOD_IDENT	(3)
#define CCT_REF_IDENT	(4)
#define CCT_EXCEPTION	(5)
#define CCT_ADVANCE	(6)
#define CCT_TERMINAL	(7)
#else
typedef enum {
    CCT_STRING,
    CCT_LABEL,
    CCT_IDENT,
    CCT_MOD_IDENT,
    CCT_REF_IDENT,
    CCT_EXCEPTION,
    CCT_ADVANCE,
    CCT_TERMINAL
} CCodeItemTypeT, *CCodeItemTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct CCodeItemT {
    struct CCodeItemT	       *next;
    CCodeItemTypeT		type;
    union {
	NStringT		string;
	EntryP			ident;
    } u;
} CCodeItemT, *CCodeItemP;

typedef struct CCodeT {
    CCodeItemP			head;
    CCodeItemP		       *tail;
    unsigned			line;
    CStringP			file;
    TypeTupleT			param;
    TypeTupleT			result;
} CCodeT, *CCodeP;

/*--------------------------------------------------------------------------*/

extern CCodeP			c_code_create
	PROTO_S ((CStringP, unsigned));
extern void			c_code_append_string
	PROTO_S ((CCodeP, NStringP));
extern void			c_code_append_label
	PROTO_S ((CCodeP, NStringP));
extern void			c_code_append_identifier
	PROTO_S ((CCodeP, NStringP));
extern void			c_code_append_modifiable
	PROTO_S ((CCodeP, NStringP));
extern void			c_code_append_reference
	PROTO_S ((CCodeP, NStringP));
extern void			c_code_append_exception
	PROTO_S ((CCodeP));
extern void			c_code_append_advance
	PROTO_S ((CCodeP));
extern void			c_code_append_terminal
	PROTO_S ((CCodeP));
extern void			c_code_check
	PROTO_S ((CCodeP, BoolT, BoolT, TypeTupleP, TypeTupleP, TableP));
extern CStringP			c_code_file
	PROTO_S ((CCodeP));
extern unsigned			c_code_line
	PROTO_S ((CCodeP));
extern TypeTupleP		c_code_param
	PROTO_S ((CCodeP));
extern TypeTupleP		c_code_result
	PROTO_S ((CCodeP));
extern void			c_code_deallocate
	PROTO_S ((CCodeP));

extern void			c_output_c_code_action
	PROTO_S ((COutputInfoP, CCodeP, TypeTupleP, TypeTupleP, SaveRStackP,
		  RuleP));
extern void			c_output_c_code_basic
	PROTO_S ((COutputInfoP, CCodeP, TypeTupleP, SaveRStackP));
extern void			c_output_c_code_assign
	PROTO_S ((COutputInfoP, CCodeP, EntryP, EntryP, EntryP, BoolT, BoolT));
extern void			c_output_c_code_param_assign
	PROTO_S ((COutputInfoP, CCodeP, EntryP, EntryP));
extern void			c_output_c_code_result_assign
	PROTO_S ((COutputInfoP, CCodeP, EntryP, EntryP));
extern void			c_output_c_code
	PROTO_S ((COutputInfoP, CCodeP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define c_code_file(c) ((c)->file)
#define c_code_line(c) ((c)->line)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_C_CODE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output")
 * eval: (include::add-path-entry "../c-output" "../generated")
 * end:
**/
