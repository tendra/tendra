/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef reform_diaginfo_key
#define reform_diaginfo_key 1

typedef struct reform_diag_info_t reform_diag_info; /* let's break a type cycle */

#else				/* been included at least once */

#ifdef reform_diagtypes_key

#ifndef reform_diaginfo_done_phase2
#define reform_diaginfo_done_phase2
				/* phase 2  */
typedef enum {
	reform_DIAG_INFO_UNINIT,
	reform_DIAG_INFO_SOURCE,
	reform_DIAG_INFO_ID,
	reform_DIAG_INFO_TYPE,
	reform_DIAG_INFO_TAG
} reform_diag_info_key;

struct reform_diag_info_t {
	reform_diag_info_key key;
	union {
		struct {
			reform_sourcemark beg;
			reform_sourcemark end;
		} source;
		struct {
			tdfstring nme;
			exp access;
			reform_diag_type typ;
		} id_scope;
		struct {
			tdfstring nme;
			reform_diag_type typ;
		} type_scope;
		struct {
			tdfstring nme;
			reform_diag_type typ;
		} tag_scope;
	} data;
};

				/* end phase 2 */
#endif				/* done phase 2 */
#endif				/* diagtypes defined */
#endif

