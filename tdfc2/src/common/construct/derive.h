/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DERIVE_INCLUDED
#define DERIVE_INCLUDED


/*
    DERIVED CLASS TYPE DECLARATIONS

    The routines in this module are concerned with the construction of
    derived and base classes.
*/

extern void add_base_class(IDENTIFIER, DECL_SPEC, int);
extern void end_base_class(CLASS_TYPE, int);
extern GRAPH expand_graph(GRAPH, int);
extern GRAPH uniq_base_class(CLASS_TYPE, ERROR *);
extern GRAPH find_base_class(CLASS_TYPE, CLASS_TYPE, int);
extern CLASS_TYPE compare_base_class(CLASS_TYPE, CLASS_TYPE, int);
extern GRAPH direct_base_class(CLASS_TYPE, CLASS_TYPE, ERROR *);
extern GRAPH find_ambig_base(GRAPH);
extern ERROR check_ambig_base(GRAPH);
extern ERROR check_virt_base(GRAPH);
extern GRAPH find_subgraph(GRAPH, GRAPH, GRAPH);
extern int is_subgraph(GRAPH, GRAPH);
extern int eq_graph(GRAPH, GRAPH);
extern GRAPH min_base_class(GRAPH);

extern IDENTIFIER search_field(NAMESPACE, HASHID, int, int);
extern IDENTIFIER search_base_field(NAMESPACE, HASHID, int, int);
extern IDENTIFIER search_subfield(NAMESPACE, GRAPH, IDENTIFIER);
extern GRAPH is_subfield(NAMESPACE, IDENTIFIER);
extern void inherit_class(void);


#endif
