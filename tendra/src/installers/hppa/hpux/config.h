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
$Log: config.h,v $
 * Revision 1.2  1998/03/16  11:25:33  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:04  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/02/14  17:19:12  wfs
 * "next_caller_offset" and "next_callee_offset" have become special tokens
 * defined in "spec_tok.c". Bug fix to a "and_tag" optimization in
 * "oprators.c". A few bug fixes in "makecode.c" arising from the variable
 * caller tests. "promote_pars" defined in "config.h".
 *
 * Revision 1.3  1996/01/08  12:01:48  wfs
 * Cosmetic changes to usage message in "hppatrans.c". "issparc" set to 0 in
 * "config.h". Change to "scan()" regarding the passing of 64 bit int params.
 *
 * Revision 1.2  1995/12/18  13:11:05  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.3  1995/10/16  14:42:39  wfs
 * *** empty log message ***
 *
 * Revision 5.2  1995/09/21  12:41:43  wfs
 * #included "compiler.h".
 *
 * Revision 5.1  1995/09/20  11:29:18  wfs
 * Added "#define isAlpha 0".
 *
 * Revision 5.0  1995/08/25  13:55:12  wfs
 * Preperation for August 95 Glue release
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:51:44  wfs
 * Removed a few sparc specific macros. Some new flags have been
 * introduced
 *
 * Revision 3.4  1995/08/25  10:51:44  wfs
 * Removed a few sparc specific macros. Some new flags have been
 * introduced
 *
 * Revision 3.1  95/04/10  16:26:01  16:26:01  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:15:49  11:15:49  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:25:32  15:25:32  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:36:39  13:36:39  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	0
#endif


/*
                              HISTORY

       The TDF->HP PA translator was based upon the TDF->MIPS translator
    written by Ian Currie <currie@rivers.dra.hmg.gb> of the UK's Defence
    Research Agency. It was developed and maintained by William Simmonds
    <William.Simmonds@rivers.dra.hmg.gb>.
*/


#define null			NULL


/* MAIN MACHINE CONFIGURATION */


/* MACHINE IDENTIFIERS */
#define is68000			0
#define is80x86			0
#define ismips			0
#define ispower			0
#define issco			0
#define issparc			0
#define isvax			0
#define ishppa                  1
#define isAlpha                 0

/* CONFIGURATION OPTIONS */
#define check_shape 		1
#define dont_unpad_apply 	1
#define has_bitfield_ops        0
#define has_byte_ops		0
#define has_byte_regs		0
#define has_neg_shift 		0
#define has_rotate              0
#define has_setcc		0
#define has64bits		0
#define keep_PIC_vars           1
#define little_end		0
#define no_bitfield_ops 	0
#define only_inline_static 	0
#define only_lengthen_ops	0
#define promote_pars            1
#define regable_union 		0
#define remove_zero_offsets 	0
#define replace_compound 	1
#define shift_is_byte 		0
#define special_fns 		0
#define substitute_complex      1
#define substitute_params 	0
#define use_long_double         1
#define value_of_null		0
#define remove_unused_counters	1
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#if 0
#define good_pointer_factor(f) ( (f) != 1 && (f) != 2 && (f) != 4 && (f) != 8 )
#else
#define good_pointer_factor(f) 1
#endif

#if use_long_double
#define target_dbl_maxexp 	16384
#else
#define target_dbl_maxexp 	308
#endif


#define DO_INDEXED_LOADS 1
#define USE_BITAD 0
#define HAS_MAGIC


#endif /* CONFIG_INCLUDED */
