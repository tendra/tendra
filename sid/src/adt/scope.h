/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * scope.h - Scope stack ADT.
 *
 * See the file "scope.c" for more information.
 */

/*   
   The scope system is only used when reading the grammar definition
   file (the .sid file). The only trace of it once the scope system
   has been deleted are the key members of the scoped rules and the
   always scope non-locals that begins with
   outer-enclosing-rule1::inner-enclosing-rule.

   Rules, actions may be scoped, non-locals must be scoped, while
   types and terminals are never scoped and are always global.
*/

#ifndef H_SCOPE
#define H_SCOPE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include "entry.h"
#include "table.h"

/* To avoid circularity: */
struct RuleT;

typedef struct ScopeMapEntryT {
    struct ScopeMapEntryT      *next;
    EntryT *			from;
    EntryT *			to;
} ScopeMapEntryT;

typedef struct ScopeStackFrameT {
    struct ScopeStackFrameT    *next;
    NStringT			scope;
    ScopeMapEntryT *		head;
    ScopeMapEntryT *	       *tail;
} ScopeStackFrameT;

typedef struct ScopeStackT {
    ScopeStackFrameT *		head;
} ScopeStackT;

void	scope_stack_init(ScopeStackT *);
void	scope_stack_push(ScopeStackT *, NStringT *);
void	scope_stack_pop(ScopeStackT *);
EntryT *	scope_stack_add_rule(ScopeStackT *, TableT *, NStringT *,
				     struct RuleT *, bool *);
EntryT *	scope_stack_add_action(ScopeStackT *, TableT *, NStringT *,
				       struct RuleT *, bool *, bool);
EntryT *	scope_stack_add_non_local(ScopeStackT *, TableT *, NStringT *,
					  EntryT *, struct RuleT *);
EntryT *	scope_stack_get_rule(ScopeStackT *, TableT *, NStringT *);
EntryT *	scope_stack_get_action(ScopeStackT *, TableT *, NStringT *);
EntryT *	scope_stack_get_non_local(ScopeStackT *, TableT *, NStringT *,
					  NStringT *);
bool	scope_stack_check_shadowing(ScopeStackT *, EntryT *,
					    struct RuleT *);

#endif /* !defined (H_SCOPE) */
