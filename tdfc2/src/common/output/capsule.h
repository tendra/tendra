/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CAPSULE_INCLUDED
#define CAPSULE_INCLUDED


/*
    TDF CAPSULE OUTPUT DECLARATIONS

    The routines in this module describe the top level TDF output.
*/

extern void init_capsule(void);
extern void init_diag(void);
extern void write_capsule(void);
extern void output_option(string);
extern BITSTREAM *enc_version(BITSTREAM *);

extern int output_tdf;
extern int output_capsule;
extern int output_all;
extern int output_bugs;
extern int output_builtin;
extern int output_date;
extern int output_diag;
extern int output_except;
extern int output_init;
extern int output_inline;
extern int output_new_diag;
extern int output_order;
extern int output_partial;
extern int output_rtti;
extern int output_shared;
extern int output_std;
extern int output_term;
extern int output_tokdec;
extern int output_unused;
extern int output_virtual;

extern int capsule_id(IDENTIFIER, int);
extern ulong capsule_no(string, int);
extern ulong capsule_name(ulong, string *, int);
extern ulong unit_no(BITSTREAM *, IDENTIFIER, int, int);
extern ulong link_no(BITSTREAM *, ulong, int);
extern void clear_no(IDENTIFIER);
extern ulong no_labels(BITSTREAM *);
extern void record_usage(ulong, int, unsigned);
extern void clear_usage(ulong, int);
extern unsigned find_usage(ulong, int);
extern void set_diag_tag(IDENTIFIER, int, ulong);
extern ulong get_diag_tag(IDENTIFIER, int);
extern void count_item(BITSTREAM *);
extern void clear_params(void);

extern BITSTREAM *tokdec_unit, *tokdef_unit;
extern BITSTREAM *tagdec_unit, *tagdef_unit;
extern BITSTREAM *aldef_unit, *linkinfo_unit;
extern BITSTREAM *diagtype_unit, *diagdef_unit, *diagcomp_unit;
extern BITSTREAM *init_func, *term_func, *term_static_func;
extern ulong init_no, term_no;
extern CLASS_TYPE last_class;
extern ulong last_params[];
extern int last_conts[];


/*
    CAPSULE VARIABLE TYPES

    These values correspond to the various types of linkable entity and
    entity groups within a TDF capsule.  They are used as arguments to
    capsule_id, unit_no etc.  VAR_label is a dummy value used for labels.
*/

enum {
	EQN_tld,
	EQN_versions,
	EQN_tokdec,
	EQN_tokdef,
	EQN_aldef,
	EQN_diagtype,
	EQN_tagdec,
	EQN_diagdef,
	EQN_dgcomp,
	EQN_tagdef,
	EQN_linkinfo,
	EQN_no,

	VAR_tag,
	VAR_token,
	VAR_alignment,
	VAR_diagtag,
	VAR_dgtag,
	VAR_no,

	VAR_label,
	VAR_total
};


/*
    USAGE INFORMATION

    These values are used to record the usage information for external
    identifiers.
*/

enum {
	USAGE_NONE   = 0x00U,
	USAGE_USE    = 0x01U,
	USAGE_DECL   = 0x02U,
	USAGE_DEFN   = 0x04U,
	USAGE_COMMON = 0x08U
};


/*
    DUMMY TAG NUMBERS

    These values give the codes for the dummy tag numbers stored in
    last_params.  The values 0-9 give the function parameter numbers.
*/

enum {
	DUMMY_this     =  0,
	DUMMY_first    =  0,
	DUMMY_second   =  1,

	DUMMY_return   = 10,
	DUMMY_copy     = 11,
	DUMMY_extra    = 12,
	DUMMY_ellipsis = 13,
	DUMMY_count    = 14,
	DUMMY_catch    = 15,
	DUMMY_token    = 16,

	DUMMY_params   = 10,
	DUMMY_max      = 20
};


#endif
