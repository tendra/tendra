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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/general_proc.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: general_proc.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:16  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:52  ma
First version.

Revision 1.3  1997/09/25 06:45:07  ma
All general_proc tests passed


--------------------------------------------------------------------------
*/

void apply_general_proc PROTO_S ((exp e, where dest, ash stack));
void tail_call PROTO_S ((exp e, where dest, ash stack));
void gcproc PROTO_S ((exp p, char* pname, long cname, int is_ext, int reg_res, diag_global* di));
void general_epilogue PROTO_S ((bool uses_caller_pointer, bool has_checkstack));
void untidy_return PROTO_S ((void));
void make_visible PROTO_S ((exp e));
void make_transformations PROTO_S ((void));
void output_env_size PROTO_S ((dec* proc, long envsize));
typedef enum {ALL, NOT_SP, NOT_A6_OR_SP} restore_type_t;
void restore_regs PROTO_S ((restore_type_t));
