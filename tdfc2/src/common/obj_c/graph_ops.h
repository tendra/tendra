/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef GRAPH_OPS_H_INCLUDED
#define GRAPH_OPS_H_INCLUDED

/* Operations for union GRAPH */

#define TAG_graph(P)			((unsigned) 0)


/* Operations for component head of union GRAPH */

#define graph_head(P)			(CHECK_NULL(P) + 0)


/* Operations for component access of union GRAPH */

#define graph_access(P)			(CHECK_NULL(P) + 1)


/* Operations for component tails of union GRAPH */

#define graph_tails(P)			(CHECK_NULL(P) + 2)


/* Operations for component top of union GRAPH */

#define graph_top(P)			(CHECK_NULL(P) + 3)


/* Operations for component equal of union GRAPH */

#define graph_equal(P)			(CHECK_NULL(P) + 4)


/* Operations for component up of union GRAPH */

#define graph_up(P)			(CHECK_NULL(P) + 5)


/* Operations for component no of union GRAPH */

#define graph_no(P)			(CHECK_NULL(P) + 6)


/* Operations for component off of union GRAPH */

#define graph_off(P)			(CHECK_NULL(P) + 7)


/* Operations for component member of union GRAPH */

#define graph_member(P)			(CHECK_NULL(P) + 8)


/* Operations for component tok1 of union GRAPH */

#define graph_tok1(P)			(CHECK_NULL(P) + 9)


/* Operations for component tok2 of union GRAPH */

#define graph_tok2(P)			(CHECK_NULL(P) + 10)


/* Operations for field basic of union GRAPH */

#define graph_basic_tag			((unsigned)0)
#define IS_graph_basic(P)		1


#define MAKE_graph_basic(head_, access_, c_class_graph)\
    {\
	c_class *x202_ = GEN_c_class(11, TYPEID_graph);\
	COPY_ctype(x202_ + 0, (head_));\
	COPY_dspec(x202_ + 1, (access_));\
	COPY_list(x202_ + 2, NULL_list ( GRAPH ));\
	COPY_graph(x202_ + 3, NULL_graph);\
	COPY_graph(x202_ + 4, NULL_graph);\
	COPY_graph(x202_ + 5, NULL_graph);\
	COPY_unsigned(x202_ + 6, 0);\
	COPY_off(x202_ + 7, NULL_off);\
	COPY_list(x202_ + 8, NULL_list ( IDENTIFIER ));\
	COPY_ulong(x202_ + 9, LINK_NONE);\
	COPY_ulong(x202_ + 10, LINK_NONE);\
	(c_class_graph) = x202_;\
    }

#define DECONS_graph_basic(head_, access_, tails_, top_, equal_, up_, no_, off_, member_, tok1_, tok2_, c_class_graph)\
    {\
	c_class *x203_ = (c_class_graph);\
	(head_) = DEREF_ctype(x203_ + 0);\
	(access_) = DEREF_dspec(x203_ + 1);\
	(tails_) = DEREF_list(x203_ + 2);\
	(top_) = DEREF_graph(x203_ + 3);\
	(equal_) = DEREF_graph(x203_ + 4);\
	(up_) = DEREF_graph(x203_ + 5);\
	(no_) = DEREF_unsigned(x203_ + 6);\
	(off_) = DEREF_off(x203_ + 7);\
	(member_) = DEREF_list(x203_ + 8);\
	(tok1_) = DEREF_ulong(x203_ + 9);\
	(tok2_) = DEREF_ulong(x203_ + 10);\
    }

#define DESTROY_graph_basic(destroyer_, head_, access_, tails_, top_, equal_, up_, no_, off_, member_, tok1_, tok2_, c_class_graph)\
    {\
	c_class *x204_ = (c_class_graph);\
	(head_) = DEREF_ctype(x204_ + 0);\
	(access_) = DEREF_dspec(x204_ + 1);\
	(tails_) = DEREF_list(x204_ + 2);\
	(top_) = DEREF_graph(x204_ + 3);\
	(equal_) = DEREF_graph(x204_ + 4);\
	(up_) = DEREF_graph(x204_ + 5);\
	(no_) = DEREF_unsigned(x204_ + 6);\
	(off_) = DEREF_off(x204_ + 7);\
	(member_) = DEREF_list(x204_ + 8);\
	(tok1_) = DEREF_ulong(x204_ + 9);\
	(tok2_) = DEREF_ulong(x204_ + 10);\
	(destroyer_)(x204_, (unsigned)11);\
    }


#endif
