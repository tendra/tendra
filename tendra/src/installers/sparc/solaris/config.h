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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/


#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

/*
    HISTORY

    The TDF->SPARC translator was based on the TDF->MIPS translator
    written by Ian Currie <currie@uk.mod.hermes> of DRA, Malvern, UK
    by Richard Wendland <richard@uk.co.praxis> of Praxis Systems plc,
    Bath, UK.  It has subsequently been maintained and developed by
    David Brownbridge <drb@uk.co.praxis> at Praxis and Robert Andrews
    <rca@uk.mod.hermes> at DRA.
*/


/* API SPECIFICATION */
#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	0
#endif

#define null			NULL


/* Settings for Solaris 2 */
#define SYSV_ABI		1
#define SYSV_AS			1
#define DWARF			0
#define target_system		"Solaris 2.4"
#define ADDUNDERSCORE		0

#define NEEDS_DEBUG_ALIGN	1


/* MACHINE IDENTIFIERS */
#define is68000			0
#define is80x86			0
#define ismips			0
#define ispower			0
#define issco			0
#define isAlpha                 0
#define issparc			1
#define isvax			0


/* CONFIGURATION OPTIONS */

#define GENCOMPAT		1
#define NEWDIAGS		1
#define NEWDWARF		1

#define has_asm			1


#define check_shape		1  /* interaction with parameter alignments is 
				      now allowed for in install_fns */
#define dont_unpad_apply	1
#define has_byte_ops		0
#define has_byte_regs		0
#define has_neg_shift		0
#define has_setcc		0
#define has64bits		0
#define keep_PIC_vars		1
#define little_end		0
#define no_bitfield_ops		0
#define only_inline_static	0
#define only_lengthen_ops	0
#define regable_union		1
#define remove_zero_offsets	0
#define replace_compound	0
#define shift_is_byte		0
#define special_fns		0
#define substitute_params	0
#define substitute_complex	1
#define use_link_stuff		SYSV_AS
#define div0_implemented 	1

/* foralls config */
#define remove_unused_counters 0
#define remove_unused_index_counters 1

#define good_index_factor(f) 0
#define good_pointer_factor(f) 1

#if SYSV_ABI
#define target_dbl_maxexp	16384
#define use_long_double		1
#else
#define target_dbl_maxexp	308
#define use_long_double		0
#endif

#define do_case_transforms 0
#define jump_table_density 10
#define non_default_entries 4
#define non_default_destinations 2

#define value_of_null 0

#define has_bitfield_ops 0

#define has_rotate 0

/* This shouldn't really be solaris specific.  It depends on whether or not
   the processor correctly implements the sdivcc and udivcc instructions. 
   These are part of the SPARC v8 architecture but their implementation
   (via software) on some implementations does not meet the specification
   with respect to overflow detection.
   */
#define DIV_SETS_CC 1	

#define diagnose_registers 1

#define HAS_MAGIC 1

#define promote_pars 1

	/* condition for shape to be treated as a struct */
#define sparccpd(s) (name(s) == cpdhd || name(s) == nofhd || \
			name(s) == shcomplexhd || shape_size(s)>64 || \
			name(s) == u64hd || name(s) == s64hd)

#endif /* CONFIG_INCLUDED */



