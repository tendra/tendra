/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:05  nonce
 *Remove ossg prototypes.  This commit is largely whitespace changes,
 *but is nonetheless important.  Here's why.
 *
 *I.  Background
 *=========================
 *
 *    The current TenDRA-4.1.2 source tree uses "ossg" prototype
 *conventions, based on the Open Systems Software Group publication "C
 *Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 *The goal behind ossg prototypes remains admirable: TenDRA should
 *support platforms that lack ANSI compliant compilers.  The explicit
 *nature of ossg's prototypes makes macro substition easy.
 *
 *    Here's an example of one function:
 *
 *    static void uop
 *	PROTO_N ( ( op, sha, a, dest, stack ) )
 *	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 *		  shape sha X exp a X where dest X ash stack )
 *    {
 *
 *tendra/src/installers/680x0/common/codec.c
 *
 *  The reasons for removing ossg are several, including:
 *
 *  0) Variables called 'X' present a problem (besides being a poor
 *variable name).
 *
 *  1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 *prototypes are easily handled by most every compiler these days.
 *
 *  2) Although TenDRA emphasizes portability, standards compliance is
 *the primary goal of the current project.  We should expect no less
 *from the compiler source code.
 *
 *  3) The benefits of complex prototypes are few, given parameter
 *promotion rules.  (Additionally, packing more types into int-sized
 *spaces tends to diminish type safety, and greatly complicates
 *debugging and testing.)
 *
 *  4) It would prove impractical to use an OSSG internal style document
 *in an open source project.
 *
 *  5) Quite frankly, ossg prototypes are difficult to read, but that's
 *certainly a matter of taste and conditioning.
 *
 *II.  Changes
 *=========================
 *
 *   This commit touches most every .h and .c file in the tendra source
 *tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 *was used to automate the following changes:
 *
 *   A.  Prototype Conversions.
 *   --------------------------------------------------
 *
 *   The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 *rewritten to ISO-compliant form.  Not every file was touched.  The
 *files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 *left for hand editing.  These files provide header generation, or have
 *non-ossg compliant headers to start with.  Scripting around these
 *would take too much time; a separate hand edit will fix them.
 *
 *   B.  Statement Spacing
 *   --------------------------------------------------
 *
 *   Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 *parenthetical lexemes.  (See the quoted example above.)  A simple
 *text substitution was made for:
 *
 *     Before            After
 *===================================
 *
 *   if ( x )            if (x)
 *   if(x)               if (x)
 *   x = 5 ;             x = 5;
 *   ... x) )            ... x))
 *
 *All of these changes are suggested by style(9).  Additional, statement
 *spacing considerations were made for all of the style(9) keywords:
 *"if" "while" "for" "return" "switch".
 *
 *A few files seem to have too few spaces around operators, e.g.:
 *
 *      arg1*arg2
 *
 *instead of
 *
 *      arg1 * arg2
 *
 *These were left for hand edits and later commits, since few files
 *needed these changes.  (At present, the rmossg.el script takes 1 hour
 *to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 *needed change would take too much time.)
 *
 *   C.  License Information
 *   --------------------------------------------------
 *
 *After useful discussion on IRC, the following license changes were
 *made:
 *
 *   1) Absent support for $License::BSD$ in the repository, license
 *and copyright information was added to each file.
 *
 *   2) Each file begins with:
 *
 *   Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *   All rights reserved.
 *
 *   Usually, copyright stays with the author of the code; however, I
 *feel very strongly that this is a group effort, and so the tendra
 *project should claim any new (c) interest.
 *
 *   3) The comment field then shows the bsd license and warranty
 *
 *   4) The comment field then shows the Crown Copyright, since our
 *changes are not yet extensive enough to claim any different.
 *
 *   5) The comment field then closes with the $TenDRA$ tag.
 *
 *   D.  Comment Formatting
 *   --------------------------------------------------
 *
 *The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *    /*
 *       Statement statement
 *       statement
 *     */
 *
 *while style(9) suggests:
 *
 *    /*
 *     * Statement statement
 *     * statement
 *     */
 *
 *Not every comment in -4.1.2 needed changing.  A parser was written to
 *identify non-compliant comments.  Note that a few comments do not
 *follow either the TenDRA-4.1.2 style or style(9), or any style I can
 *recognize.  These need hand fixing.
 *
 *   E.  Indentation
 *   --------------------------------------------------
 *
 *   A elisp tendra-c-mode was created to define how code should be
 *indented.  The structure follows style(9) in the following regards:
 *
 *  (c-set-offset 'substatement-open 0)
 *  (setq c-indent-tabs-mode t
 *	c-indent-level 4
 *	c-argdecl-indent t
 *	c-tab-always-indent t
 *	backward-delete-function nil
 *	c-basic-offset 4
 *	tab-width 4))
 *
 *This means that substatement opening are not indented.  E.g.:
 *
 *   if (condition)
 *   {
 *
 *instead of
 *
 *   if (condition)
 *     {
 *
 *or even
 *
 *   if (condition) {
 *
 *Each statement is indented by a tab instead of a spaces.  Set your tab
 *stop to comply with style(9); see the vim resources in the tendra
 *tree.  I'll add the emacs mode support shortly.
 *
 *No doubt, a function or two escaped change because of unusual
 *circumstances.  These must be hand fixed as well.
 *
 *III.  Things Not Changed
 *=========================
 *
 *    A large number of style(9) deficiencies remain.  These will
 *require a separate effort.  I decided to stop with the changes noted
 *above because:
 *
 *   0)  The script currently takes hours to run to completion even on
 *high-end consumer machines.
 *
 *   1)  We need to move on and fix other substantive problems.
 *
 *   2) The goal of this commit was *just* ossg removal; I took the
 *opportunity to get other major white-space issues out of the way.
 *
 *    I'll also note that despite this commit, a few ossg issues remain.
 *These include:
 *
 *   0) The ossg headers remain.  They contain useful flags needed by
 *other operations.  Additionally, the BUILD_ERRORS perl script still
 *generates ossg-compliant headers.  (This is being removed as we change
 *the build process.)
 *
 *   1) A few patches of code check for ossg flags: "if (ossg) etc."
 *These can be hand removed as well.
 *
 *   2) No doubt, a few ossg headers escaped the elisp script.  We can
 *address these seriatim.
 *
 *IV.  Testing
 *=========================
 *
 *    Without a complete build or test suite, it's difficult to
 *determine if these changes have introduced any bugs.  I've identified
 *several situations where removal of ossg caused bugs in sid and
 *calculus operations.  The elisp script avoids these situations; we
 *will hand edit a few files.
 *
 *    As is, the changes should behave properly; the source base builds
 *the same before and after the rmossg.el script is run.  Nonetheless,
 *please note that this commit changes over 23,000 PROTO declarations,
 *and countless line changes.  I'll work closely with any developers
 *affected by this change.
 *
 * Revision 1.2  1998/03/11  11:03:39  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1997/12/05  10:23:58  pwe
 * name change
 *
 * Revision 1.5  1997/12/04  19:41:18  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.4  1997/10/23  09:27:28  pwe
 * ANDF-DE v1.7, extra diags
 *
 * Revision 1.3  1997/10/10  18:18:26  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/04/17  11:50:17  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.1  1997/03/20  16:09:05  pwe
 * first version
 *
 **********************************************************************/

/**********************************************************************
 *The identifier names and values in the first part of this file were derived from
 *
 *DWARF Debugging Information Format, Revision 2.0.0, July 27, 1993
 **********************************************************************/

#define DWARF_VERSION	2


#define DW_TAG_array_type		0x01
#define DW_TAG_class_type		0x02
#define DW_TAG_entry_point		0x03
#define DW_TAG_enumeration_type		0x04
#define DW_TAG_formal_parameter		0x05
#define DW_TAG_imported_declaration	0x08
#define DW_TAG_label			0x0a
#define DW_TAG_lexical_block		0x0b
#define DW_TAG_member			0x0d
#define DW_TAG_pointer_type		0x0f
#define DW_TAG_reference_type		0x10
#define DW_TAG_compile_unit		0x11
#define DW_TAG_string_type		0x12
#define DW_TAG_structure_type		0x13
#define DW_TAG_subroutine_type		0x15
#define DW_TAG_typedef			0x16
#define DW_TAG_union_type		0x17
#define DW_TAG_unspecified_parameters	0x18
#define DW_TAG_variant			0x19
#define DW_TAG_common_block		0x1a
#define DW_TAG_common_inclusion		0x1b
#define DW_TAG_inheritance		0x1c
#define DW_TAG_inlined_subroutine	0x1d
#define DW_TAG_module			0x1e
#define DW_TAG_ptr_to_member_type	0x1f
#define DW_TAG_set_type			0x20
#define DW_TAG_subrange_type		0x21
#define DW_TAG_with_stmt		0x22
#define DW_TAG_access_declaration	0x23
#define DW_TAG_base_type		0x24
#define DW_TAG_catch_block		0x25
#define DW_TAG_const_type		0x26
#define DW_TAG_constant			0x27
#define DW_TAG_enumerator		0x28
#define DW_TAG_file_type		0x29
#define DW_TAG_friend			0x2a
#define DW_TAG_namelist			0x2b
#define DW_TAG_namelist_item		0x2c
#define DW_TAG_packed_type		0x2d
#define DW_TAG_subprogram		0x2e
#define DW_TAG_template_type_param	0x2f
#define DW_TAG_template_value_param	0x30
#define DW_TAG_thrown_type		0x31
#define DW_TAG_try_block		0x32
#define DW_TAG_variant_part		0x33
#define DW_TAG_variable			0x34
#define DW_TAG_volatile_type		0x35
#define DW_TAG_lo_user			0x4080
#define DW_TAG_hi_user			0xffff


#define DW_CHILDREN_no			0
#define DW_CHILDREN_yes			1


#define DW_AT_sibling			0x01
#define DW_AT_location			0x02
#define DW_AT_name			0x03
#define DW_AT_ordering			0x09
#define DW_AT_byte_size			0x0b
#define DW_AT_bit_offset		0x0c
#define DW_AT_bit_size			0x0d
#define DW_AT_stmt_list			0x10
#define DW_AT_low_pc			0x11
#define DW_AT_high_pc			0x12
#define DW_AT_language			0x13
#define DW_AT_discr			0x15
#define DW_AT_discr_value		0x16
#define DW_AT_visibility		0x17
#define DW_AT_import			0x18
#define DW_AT_string_length		0x19
#define DW_AT_common_reference		0x1a
#define DW_AT_comp_dir			0x1b
#define DW_AT_const_value		0x1c
#define DW_AT_containing_type		0x1d
#define DW_AT_default_value		0x1e
#define DW_AT_inline			0x20
#define DW_AT_is_optional		0x21
#define DW_AT_lower_bound		0x22
#define DW_AT_producer			0x25
#define DW_AT_prototyped		0x27
#define DW_AT_return_addr		0x2a
#define DW_AT_start_scope		0x2c
#define DW_AT_stride_size		0x2e
#define DW_AT_upper_bound		0x2f
#define DW_AT_abstract_origin		0x31
#define DW_AT_accessibility		0x32
#define DW_AT_address_class		0x33
#define DW_AT_artificial		0x34
#define DW_AT_base_types		0x35
#define DW_AT_calling_convention	0x36
#define DW_AT_count			0x37
#define DW_AT_data_member_location	0x38
#define DW_AT_decl_column		0x39
#define DW_AT_decl_file			0x3a
#define DW_AT_decl_line			0x3b
#define DW_AT_declaration		0x3c
#define DW_AT_discr_list		0x3d
#define DW_AT_encoding			0x3e
#define DW_AT_external			0x3f
#define DW_AT_frame_base		0x40
#define DW_AT_friend			0x41
#define DW_AT_identifier_case		0x42
#define DW_AT_macro_info		0x43
#define DW_AT_namelist_item		0x44
#define DW_AT_priority			0x45
#define DW_AT_segment			0x46
#define DW_AT_specification		0x47
#define DW_AT_static_link		0x48
#define DW_AT_type			0x49
#define DW_AT_use_location		0x4a
#define DW_AT_variable_parameter	0x4b
#define DW_AT_virtuality		0x4c
#define DW_AT_vtable_elem_location	0x4d
#define DW_AT_lo_user			0x2000
#define DW_AT_hi_user			0x3fff


#define DW_FORM_addr			0x01
#define DW_FORM_block2			0x03
#define DW_FORM_block4			0x04
#define DW_FORM_data2			0x05
#define DW_FORM_data4			0x06
#define DW_FORM_data8			0x07
#define DW_FORM_string			0x08
#define DW_FORM_block			0x09
#define DW_FORM_block1			0x0a
#define DW_FORM_data1			0x0b
#define DW_FORM_flag			0x0c
#define DW_FORM_sdata			0x0d
#define DW_FORM_strp			0x0e
#define DW_FORM_udata			0x0f
#define DW_FORM_ref_addr		0x10
#define DW_FORM_ref1			0x11
#define DW_FORM_ref2			0x12
#define DW_FORM_ref4			0x13
#define DW_FORM_ref8			0x14
#define DW_FORM_ref_udata		0x15
#define DW_FORM_indirect		0x16


#define DW_OP_addr			0x03
#define DW_OP_deref			0x06
#define DW_OP_const1u			0x08
#define DW_OP_const1s			0x09
#define DW_OP_const2u			0x0a
#define DW_OP_const2s			0x0b
#define DW_OP_const4u			0x0c
#define DW_OP_const4s			0x0d
#define DW_OP_const8u			0x0e
#define DW_OP_const8s			0x0f
#define DW_OP_constu			0x10
#define DW_OP_consts			0x11
#define DW_OP_dup			0x12
#define DW_OP_drop			0x13
#define DW_OP_over			0x14
#define DW_OP_pick			0x15
#define DW_OP_swap			0x16
#define DW_OP_rot			0x17
#define DW_OP_xderef			0x18
#define DW_OP_abs			0x19
#define DW_OP_and			0x1a
#define DW_OP_div			0x1b
#define DW_OP_minus			0x1c
#define DW_OP_mod			0x1d
#define DW_OP_mul			0x1e
#define DW_OP_neg			0x1f
#define DW_OP_not			0x20
#define DW_OP_or			0x21
#define DW_OP_plus			0x22
#define DW_OP_plus_uconst		0x23
#define DW_OP_shl			0x24
#define DW_OP_shr			0x25
#define DW_OP_shra			0x26
#define DW_OP_xor			0x27
#define DW_OP_skip			0x2f
#define DW_OP_bra			0x28
#define DW_OP_eq			0x29
#define DW_OP_ge			0x2a
#define DW_OP_gt			0x2b
#define DW_OP_le			0x2c
#define DW_OP_lt			0x2d
#define DW_OP_ne			0x2e
#define DW_OP_lit0			0x30
#define DW_OP_lit1			0x31
#define DW_OP_lit31			0x4f
#define DW_OP_reg0			0x50
#define DW_OP_reg1			0x51
#define DW_OP_reg31			0x6f
#define DW_OP_breg0			0x70
#define DW_OP_breg1			0x71
#define DW_OP_breg31			0x8f
#define DW_OP_regx			0x90
#define DW_OP_fbreg			0x91
#define DW_OP_bregx			0x92
#define DW_OP_piece			0x93
#define DW_OP_deref_size		0x94
#define DW_OP_xderef_size		0x95
#define DW_OP_nop			0x96
#define DW_OP_lo_user			0xe0
#define DW_OP_hi_user			0xff


#define DW_ATE_address			0x1
#define DW_ATE_boolean			0x2
#define DW_ATE_complex_float		0x3
#define DW_ATE_float			0x4
#define DW_ATE_signed			0x5
#define DW_ATE_signed_char		0x6
#define DW_ATE_unsigned			0x7
#define DW_ATE_unsigned_char		0x8
#define DW_ATE_lo_user			0x80
#define DW_ATE_hi_user			0xff


#define DW_ACCESS_public		1
#define DW_ACCESS_protected		2
#define DW_ACCESS_private		3


#define DW_VIS_local			1
#define DW_VIS_exported			2
#define DW_VIS_qualified		3


#define DW_VIRTUALITY_none		0
#define DW_VIRTUALITY_virtual		1
#define DW_VIRTUALITY_pure_virtual	2


#define DW_LANG_C89			0x0001
#define DW_LANG_C			0x0002
#define DW_LANG_Ada83			0x0003
#define DW_LANG_C_plus_plus		0x0004
#define DW_LANG_Cobol74			0x0005
#define DW_LANG_Cobol85			0x0006
#define DW_LANG_Fortran77		0x0007
#define DW_LANG_Fortran90		0x0008
#define DW_LANG_Pascal83		0x0009
#define DW_LANG_Modula2			0x000a
#define DW_LANG_lo_user			0x8000
#define DW_LANG_hi_user			0xffff


#define DW_ID_case_sensitive		0
#define DW_ID_up_case			1
#define DW_ID_down_case			2
#define DW_ID_case_insensitive		3


#define DW_CC_normal			0x1
#define DW_CC_program			0x2
#define DW_CC_nocall			0x3
#define DW_CC_lo_user			0x40
#define DW_CC_hi_user			0xff


#define DW_INL_not_inlined		0
#define DW_INL_inlined			1
#define DW_INL_declared_not_inlined	2
#define DW_INL_declared_inlined		3


#define DW_ORD_row_major		0
#define DW_ORD_col_major		1


#define DW_DSC_label			0
#define DW_DSC_range			1


#define DW_LNS_copy			1
#define DW_LNS_advance_pc		2
#define DW_LNS_advance_line		3
#define DW_LNS_set_file			4
#define DW_LNS_set_column		5
#define DW_LNS_negate_stmt		6
#define DW_LNS_set_basic_block		7
#define DW_LNS_const_add_pc		8
#define DW_LNS_fixed_advance_pc		9


#define DW_LNE_end_sequence		1
#define DW_LNE_set_address		2
#define DW_LNE_define_file		3


#define DW_MACINFO_define		1
#define DW_MACINFO_undef		2
#define DW_MACINFO_start_file		3
#define DW_MACINFO_end_file		4
#define DW_MACINFO_vendor_ext		255


#define DW_CFA_advance_loc		0x40
#define DW_CFA_offset			0x80
#define DW_CFA_restore			0xc0
#define DW_CFA_set_loc			0x01
#define DW_CFA_advance_loc1		0x02
#define DW_CFA_advance_loc2		0x03
#define DW_CFA_advance_loc4		0x04
#define DW_CFA_offset_extended		0x05
#define DW_CFA_restore_extended		0x06
#define DW_CFA_undefined		0x07
#define DW_CFA_same_value		0x08
#define DW_CFA_register			0x09
#define DW_CFA_remember_state		0x0a
#define DW_CFA_restore_state		0x0b
#define DW_CFA_def_cfa			0x0c
#define DW_CFA_def_cfa_register		0x0d
#define DW_CFA_def_cfa_offset		0x0e
#define DW_CFA_nop			0
#define DW_CFA_lo_user			0x1c
#define DW_CFA_hi_user			0x3f


#define DW_CIE_id	0xffffffff
#define DW_CIE_VERSION	1


/* Proposed extensions */

#define DW_CFA_DD_def_cfa_inc_offset	(DW_CFA_lo_user + 1)
#define DW_CFA_DD_def_cfa_dec_offset	(DW_CFA_lo_user + 2)
#define DW_CFA_DD_def_cfa_fixed_offset	(DW_CFA_lo_user + 3)

#define DW_CFA_DD_sparc_save_regwindow	(DW_CFA_lo_user + 4)
#define DW_CFA_DD_sparc_restore_regwindow  (DW_CFA_lo_user + 5)

#define DW_CFA_DD_location		(DW_CFA_lo_user + 6)


#define DW_TAG_DD_lexical_fragment	(DW_TAG_lo_user + 0x00)
#define DW_TAG_DD_foreign_source	(DW_TAG_lo_user + 0x02)
#define DW_TAG_DD_subroutine_call	(DW_TAG_lo_user + 0x03)
#define DW_TAG_DD_subroutine_return	(DW_TAG_lo_user + 0x04)
#define DW_TAG_DD_breakpoint		(DW_TAG_lo_user + 0x05)
#define DW_TAG_DD_destruct		(DW_TAG_lo_user + 0x06)
#define DW_TAG_DD_branch		(DW_TAG_lo_user + 0x07)
#define DW_TAG_DD_test			(DW_TAG_lo_user + 0x08)
#define DW_TAG_DD_jump			(DW_TAG_lo_user + 0x09)
#define DW_TAG_DD_long_jump		(DW_TAG_lo_user + 0x0a)
#define DW_TAG_DD_throw			(DW_TAG_lo_user + 0x0b)
#define DW_TAG_DD_namespace		(DW_TAG_lo_user + 0x0c)
#define DW_TAG_DD_indirect_member	(DW_TAG_lo_user + 0x0d)
#define DW_TAG_DD_template_proc_param	(DW_TAG_lo_user + 0x0e)
#define DW_TAG_DD_template_module_param	(DW_TAG_lo_user + 0x0f)
#define DW_TAG_DD_class_wide_type	(DW_TAG_lo_user + 0x11)
#define DW_TAG_DD_aliased_type		(DW_TAG_lo_user + 0x12)
#define DW_TAG_DD_task_type		(DW_TAG_lo_user + 0x13)
#define DW_TAG_DD_synchronized_type	(DW_TAG_lo_user + 0x14)
#define DW_TAG_DD_entry			(DW_TAG_lo_user + 0x15)
#define DW_TAG_DD_entry_barrier		(DW_TAG_lo_user + 0x16)
#define DW_TAG_DD_select		(DW_TAG_lo_user + 0x17)
#define DW_TAG_DD_accept		(DW_TAG_lo_user + 0x18)
#define DW_TAG_DD_rts_call		(DW_TAG_lo_user + 0x19)
#define DW_TAG_DD_entrycall_alt		(DW_TAG_lo_user + 0x1a)
#define DW_TAG_DD_select_alternative	(DW_TAG_lo_user + 0x1b)
#define DW_TAG_DD_select_guard		(DW_TAG_lo_user + 0x1c)
#define DW_TAG_DD_asynchronous_select	(DW_TAG_lo_user + 0x1d)
#define DW_TAG_DD_triggering_alternate	(DW_TAG_lo_user + 0x1e)
#define DW_TAG_DD_abortable_part	(DW_TAG_lo_user + 0x1f)
#define DW_TAG_DD_floating_digits_type	(DW_TAG_lo_user + 0x20)
#define DW_TAG_DD_fixed_point_type	(DW_TAG_lo_user + 0x21)
#define DW_TAG_DD_limited_type		(DW_TAG_lo_user + 0x22)
#define DW_TAG_DD_modular_type		(DW_TAG_lo_user + 0x23)
#define DW_TAG_DD_requeue		(DW_TAG_lo_user + 0x24)
#define DW_TAG_DD_constraint		(DW_TAG_lo_user + 0x25)
#define DW_TAG_DD_subunit		(DW_TAG_lo_user + 0x26)
#define DW_TAG_DD_child_unit		(DW_TAG_lo_user + 0x27)
#define DW_TAG_DD_incomplete_type	(DW_TAG_lo_user + 0x28)
#define DW_TAG_DD_source_span		(DW_TAG_lo_user + 0x29)
#define DW_TAG_DD_source_start		(DW_TAG_lo_user + 0x2a)
#define DW_TAG_DD_source_end		(DW_TAG_lo_user + 0x2b)

#define DW_TAG_DD_optimisation_block	(DW_TAG_lo_user + 0x2c)
#define DW_TAG_DD_moved_code		(DW_TAG_lo_user + 0x2d)
#define DW_TAG_DD_absent_code		(DW_TAG_lo_user + 0x2e)


#define DW_AT_DD_indirect_attributes	(DW_AT_lo_user + 0x01)
#define DW_AT_DD_import_kind		(DW_AT_lo_user + 0x02)
#define DW_AT_DD_elaboration		(DW_AT_lo_user + 0x03)
#define DW_AT_DD_generic_name		(DW_AT_lo_user + 0x04)
#define DW_AT_DD_barrier		(DW_AT_lo_user + 0x05)
#define DW_AT_DD_begin			(DW_AT_lo_user + 0x06)
#define DW_AT_DD_newtype		(DW_AT_lo_user + 0x07)
#define DW_AT_DD_heap_only_pointer	(DW_AT_lo_user + 0x08)
#define DW_AT_DD_discriminant		(DW_AT_lo_user + 0x09)
#define DW_AT_DD_digits			(DW_AT_lo_user + 0x0a)
#define DW_AT_DD_delta			(DW_AT_lo_user + 0x0b)
#define DW_AT_DD_call_kind		(DW_AT_lo_user + 0x0c)
#define DW_AT_DD_module			(DW_AT_lo_user + 0x0d)
#define DW_AT_DD_rtti_static		(DW_AT_lo_user + 0x0f)
#define DW_AT_DD_rtti_dynamic		(DW_AT_lo_user + 0x10)
#define DW_AT_DD_task_control_block	(DW_AT_lo_user + 0x11)
#define DW_AT_DD_so_control_block	(DW_AT_lo_user + 0x12)
#define DW_AT_DD_entry_spec		(DW_AT_lo_user + 0x13)
#define DW_AT_DD_alt			(DW_AT_lo_user + 0x14)
#define DW_AT_DD_alt_kind		(DW_AT_lo_user + 0x15)
#define DW_AT_DD_alt_no			(DW_AT_lo_user + 0x16)
#define DW_AT_DD_repn			(DW_AT_lo_user + 0x17)
#define DW_AT_DD_jump_pc		(DW_AT_lo_user + 0x18)
#define DW_AT_DD_cont_pc		(DW_AT_lo_user + 0x19)
#define DW_AT_DD_abort			(DW_AT_lo_user + 0x1a)
#define DW_AT_DD_constraint_ref		(DW_AT_lo_user + 0x1b)
#define DW_AT_DD_task_id		(DW_AT_lo_user + 0x1c)
#define DW_AT_DD_vtable_static		(DW_AT_lo_user + 0x1d)
#define DW_AT_DD_vtable_dynamic		(DW_AT_lo_user + 0x1e)
#define DW_AT_DD_separate		(DW_AT_lo_user + 0x20)
#define DW_AT_DD_parent			(DW_AT_lo_user + 0x21)
#define DW_AT_DD_ada_derived		(DW_AT_lo_user + 0x22)
#define DW_AT_DD_small_value		(DW_AT_lo_user + 0x23)
/* #define DW_AT_DD_computed_default	(DW_AT_lo_user + 0x24) */

#define DW_AT_DD_optimisation_kind	(DW_AT_lo_user + 0x25)
#define DW_AT_DD_optim_ref		(DW_AT_lo_user + 0x26)
#define DW_AT_DD_obj_noassgn		(DW_AT_lo_user + 0x27)
#define DW_AT_DD_obj_assgn		(DW_AT_lo_user + 0x28)
#define DW_AT_DD_ext_location		(DW_AT_lo_user + 0x29)

