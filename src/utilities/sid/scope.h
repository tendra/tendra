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


/*** scope.h --- Scope stack ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "scope.c" for more information.
 *
 *** Change Log:
 * $Log: scope.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:59:04  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:43  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_SCOPE
#define H_SCOPE

#include "os-interface.h"
#include "dstring.h"
#include "entry.h"
#include "table.h"

/* To avoid circularity: */
struct RuleT;

/*--------------------------------------------------------------------------*/

typedef struct ScopeMapEntryT {
    struct ScopeMapEntryT      *next;
    EntryP			from;
    EntryP			to;
} ScopeMapEntryT, *ScopeMapEntryP;

typedef struct ScopeStackFrameT {
    struct ScopeStackFrameT    *next;
    NStringT			scope;
    ScopeMapEntryP		head;
    ScopeMapEntryP	       *tail;
} ScopeStackFrameT, *ScopeStackFrameP;

typedef struct ScopeStackT {
    ScopeStackFrameP		head;
} ScopeStackT, *ScopeStackP;

/*--------------------------------------------------------------------------*/

extern void			scope_stack_init
	PROTO_S ((ScopeStackP));
extern void			scope_stack_push
	PROTO_S ((ScopeStackP, NStringP));
extern void			scope_stack_pop
	PROTO_S ((ScopeStackP));
extern EntryP			scope_stack_add_rule
	PROTO_S ((ScopeStackP, TableP, NStringP, struct RuleT *, BoolT *));
extern EntryP			scope_stack_add_action
	PROTO_S ((ScopeStackP, TableP, NStringP, struct RuleT *, BoolT *));
extern EntryP			scope_stack_add_non_local
	PROTO_S ((ScopeStackP, TableP, NStringP, EntryP, struct RuleT *));
extern EntryP			scope_stack_get_rule
	PROTO_S ((ScopeStackP, TableP, NStringP));
extern EntryP			scope_stack_get_action
	PROTO_S ((ScopeStackP, TableP, NStringP));
extern EntryP			scope_stack_get_non_local
	PROTO_S ((ScopeStackP, TableP, NStringP, NStringP));
extern BoolT			scope_stack_check_shadowing
	PROTO_S ((ScopeStackP, EntryP, struct RuleT *));

#endif /* !defined (H_SCOPE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
