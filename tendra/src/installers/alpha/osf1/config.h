/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/* 	$Id$	 */
/**/
#ifndef config_key
#define config_key 1

#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_64_BIT
#define FS_64_BIT		1
#endif

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	1
#endif

#define isvax 0
#define ismips 0
#define is68000 0
#define is80x86 0
#define ispower 0
#define issparc 0
#define isAlpha 1
#define is80586 0

#define issco 0

#define has_setcc 0
#define little_end 1
#define has_byte_regs 0
#define has_byte_ops 0
#define only_lengthen_ops 1
#define has_neg_shift 0
#define regable_union 0
#define substitute_params 1
#define special_fns 0
#define shift_is_byte 1
#define only_inline_static 0

#define remove_zero_offsets 1
#define replace_compound 1
#define no_bitfield_ops 0
#define dont_unpad_apply 0

#define target_dbl_maxexp 308

#define check_shape 1
#define has64bits 1
#define maxmin_implemented 0

#define temp_mips 0

/* settings for foralls optimisations */
#define remove_unused_counters 1
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#define good_pointer_factor(f) 1


#define div0_implemented 0

#define condassign_implemented 0

#define substitute_complex 1

#define do_case_transforms 0  /* This does not work on the alpha */
#define jump_table_density 10
#define non_default_entries 0 /* 4 */
#define non_default_destinations 2

#define value_of_null 0

#define has_bitfield_ops 0
#define has_rotate 0

#ifndef DO_SCHEDULE
#define DO_SCHEDULE 0
#endif

#define diagnose_registers 1

#define HAS_MAGIC 1

#define RDATA_INSTR ".rdata"
#define SDATA_INSTR ".sdata"
#define VERSION_INSTR ".verstamp %d %d"

#define USAGE_STRING "alphatrans -[ABCDEFHIKMPQRSUXVWZu] file.t file.G file.T [file.s]"

#endif
