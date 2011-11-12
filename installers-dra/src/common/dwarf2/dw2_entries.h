/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef entries_tag
#define entries_tag 1


typedef struct {
	int	index;
	long	*attr;
	long	valid;
	long	special;
#if 1
	char	*aname;
#endif
} abbrev_entry;

extern abbrev_entry
  dwe_comp_unit,
  dwe_cmac_unit,
  dwe_module,
  dwe_namespace,
  dwe_subunit,
  dwe_childunit,
  dwe_child_acc,
  dwe_import,
  dwe_import_p,
  dwe_entrypt,
  dwe_param,
  dwe_formal,
  dwe_opt_par,
  dwe_thrown_t,
  dwe_inl_call,
  dwe_inl_opnd,
  dwe_scope,
  dwe_fragment,
  dwe_label,
  dwe_with,
  dwe_try,
  dwe_catch,
  dwe_variable,
  dwe_constant,
  dwe_tmpl_type,
  dwe_tmpl_val,
  dwe_tmpl_proc,
  dwe_tmpl_mod,
  dwe_typedef,
  dwe_typecon,
  dwe_cnstraint,
  dwe_base_type,
  dwe_cnst_type,
  dwe_vol_type,
  dwe_clwd_type,
  dwe_als_type,
  dwe_lim_type,
  dwe_ptr_type,
  dwe_hpptr_t,
  dwe_ref_type,
  dwe_pack_type,
  dwe_arr_type,
  dwe_arr_dyn,
  dwe_subr_type,
  dwe_enum_type,
  dwe_enum_tor,
  dwe_enum_char,
  dwe_struct_t,
  dwe_member,
  dwe_varpart,
  dwe_varpart_t,
  dwe_variant_0,
  dwe_variant_1,
  dwe_variant_n,
  dwe_union_t,
  dwe_class_t,
  dwe_inheritce,
  dwe_friend,
  dwe_ptrmem_t,
  dwe_ind_mem,
  dwe_proc_type,
  dwe_procv_t,
  dwe_string_t,
  dwe_stringc_t,
  dwe_file_t,
  dwe_set_t,
  dwe_fixpt_t,
  dwe_fldg_t,
  dwe_modular_t,
  dwe_task_t,
  dwe_synch_t,
  dwe_entry,
  dwe_for_unit,
  dwe_for_lang,
  dwe_call,
  dwe_return,
  dwe_destruct,
  dwe_branch,
  dwe_branch_0,
  dwe_break,
  dwe_test,
  dwe_test_0,
  dwe_jump,
  dwe_jump_0,
  dwe_lj,
  dwe_lj_0,
  dwe_throw,
  dwe_barrier,
  dwe_select,
  dwe_accept,
  dwe_accept_c,
  dwe_rts,
  dwe_rts_en,
  dwe_sel_alt,
  dwe_sel_alt_c,
  dwe_sel_guard,
  dwe_asynchsel,
  dwe_trigger,
  dwe_trigger_c,
  dwe_abort_pt,
  dwe_abort_ptc,
  dwe_requeue,
  dwe_unknown_t,
  dwe_span,
  dwe_span_strt,
  dwe_span_end,
  dwe_absent,
  dwe_absent_r,
  dwe_absent_x,
  dwe_absent_xr,
  dwe_displaced,
  dwe_displ_x,
  dwe_moved,
  dwe_moved_r,
  dwe_moved_x,
  dwe_moved_xr,
  dwe_optim,
  dwe_proc;

extern void init_dw_entries(void);

extern long dw_entry(abbrev_entry en, long attr);



	/* general attributes */

#define H_AO	0x1		/* inline abstract origin */
#define H_SP	0x2		/* ref specification */
#define H_DC	0x4		/* declaration only */
#define H_NM	0x8		/* has name */
#define H_XY	0x10		/* has source coordinates */
#define H_EX	0x20		/* flag for external */
#define H_AT	0x40		/* has artificiality */
#define H_AC	0x80		/* has accessibility */
#define H_TP	0x100		/* has type */
#define H_SS	0x200		/* has start scope */
#define H_RP	0x400		/* has repn clause */
#define H_GN	0x800		/* generic name */
#define H_EL	0x1000		/* has elaboration */
#define H_SE	0x2000		/* Ada is separate */

	/* attributes for functions */

#define H_PC	0x10000		/* has code address */
#define H_CC	0x20000		/* has calling convention */
#define H_PT	0x40000		/* has prototype */
#define H_IL	0x80000		/* inlined */
#define H_VT	0x100000	/* has virtuality */
#define H_VL	0x200000	/* vtable elem location */
#define H_SL	0x400000	/* has static link */
#define H_LN	0x800000	/* has language call convention */

	/* attributes for objects */

#define H_CV	0x10000		/* has const value */
#define H_LC	0x20000		/* has single location  */
#define H_LL	0x40000		/* has location list */
#define H_LE	0x80000		/* has extended loclist */
#define H_VP	0x100000	/* variable parameter */
#define H_DF	0x200000	/* default value */
#if 0
#define H_DX	0x400000	/* default existance */
#endif

	/* attributes for lex_scopes */

/*	H_PC	0x10000	*/
#define H_BG	0x20000		/* has 'BEGIN' */

	/* attributes for types */

#define H_SZ	0x10000		/* has byte size */
#define H_NW	0x20000		/* is new */
#define H_AD	0x40000		/* Ada derived */

	/* attributes for bounds */

#define H_LB	0x40000		/* lower bound */
#define H_UB	0x80000		/* upper bound */
#define H_CN	0x100000	/* count */

	/* attributes for members */

/*	H_LC	0x20000	*/
#define H_BF	0x10000		/* bitfield */
#define H_DS	0x40000		/* discriminant */
/*	H_DF	0x100000 */
/*	H_DX	0x200000 REMOVE	*/

	/* attributes for class types */

/*	H_AD	0x40000 */
#define H_VS	0x100000	/* vtable static */
#define H_VD	0x200000	/* vtable dynamic */
#define H_RS	0x400000	/* rtti static */
#define H_RD	0x800000	/* rtti dynamic */

	/* attributes for Ada tasks and Synchronised types */

#define H_CB	0x100000	/* control block */
#define H_ID	0x200000	/* task id */

	/* attributes for constraints */

#define	H_RM	0x800000	/* ref member */
/*	H_TP	0x100 */
/*	H_CV	0x10000 */

	/* attributes for fixed point type */

/*	H_DF	0x100000    delta */
/*	H_DS	0x40000     digits */

#define H_EXTN	0x80000000

#endif
