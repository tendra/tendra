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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/sunos/config.h,v 1.3 1998/03/16 11:25:38 release Exp $
--------------------------------------------------------------------------
$Log: config.h,v $
 * Revision 1.3  1998/03/16  11:25:38  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.2  1998/03/11  11:04:08  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1998/01/11  15:18:01  pwe
 * remove NEWDIAGS
 *
 * Revision 1.2  1997/04/01  17:17:59  pwe
 * diagnose pl_tests
 *
 * Revision 1.1  1997/03/24  17:10:10  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.13  1996/08/23  12:07:53  pwe
 * treat complex parameter as struct
 *
 * Revision 1.12  1996/08/15  15:34:48  pwe
 * mod for PWE ownership
 *
 * Revision 1.11  1996/04/16  10:53:36  john
 * Changed comment
 *
 * Revision 1.10  1996/01/25  16:09:58  john
 * Removed shape check
 *
 * Revision 1.9  1995/12/15  10:11:55  john
 * Added promote_pars
 *
 * Revision 1.8  1995/09/20  12:29:53  john
 * Change to common flag
 *
 * Revision 1.7  1995/09/13  11:00:40  john
 * added HAS_MAGIC flag
 *
 * Revision 1.6  1995/09/13  08:17:49  john
 * *** empty log message ***
 *
 * Revision 1.5  1995/07/20  15:39:40  john
 * added definition of diagnose_registers
 *
 * Revision 1.4  1995/07/14  16:30:06  john
 * Added new flag
 *
 * Revision 1.3  1995/06/27  08:47:05  john
 * Added has_rotate definition
 *
 * Revision 1.2  1995/05/26  12:57:09  john
 * New option: has_bitfield_ops
 *
 * Revision 1.1.1.1  1995/03/13  10:18:30  john
 * Entered into CVS
 *
 * Revision 1.7  1995/01/10  09:34:46  john
 * Added definition of value_of_null
 *
 * Revision 1.6  1995/01/10  09:34:03  john
 * Added configuration macros for case transform code.
 *
 * Revision 1.5  1994/10/26  13:49:55  djch
 * now use good_pointer_factor for bettere speed
 *
 * Revision 1.4  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.3  1994/07/04  08:35:10  djch
 * added target_system name. added div0_implemented and
 * remove_unused_index_counters
 *
 * Revision 1.2  1994/05/24  12:03:52  djch
 * Added parameters for the new foralls.c - initial values form pdh
 *
 * Revision 1.1  1994/05/03  14:50:09  djch
 * Initial revision
 *
 * Revision 1.5  94/02/21  16:10:35  16:10:35  ra (Robert Andrews)
 * Move compiler stuff into compiler.h.
 * 
 * Revision 1.4  93/09/27  14:40:48  14:40:48  ra (Robert Andrews)
 * Make use_long_double and target_dbl_maxexp depend on the value of
 * SYSV_ABI.  Introduce use_link_stuff to control output of System V
 * .ident and .weak directives.
 * 
 * Revision 1.3  93/08/18  11:09:18  11:09:18  ra (Robert Andrews)
 * Changed method of specifying UNIX_SV and SOLARIS versions (just define
 * these macros).
 * 
 * Revision 1.2  93/07/08  18:18:57  18:18:57  ra (Robert Andrews)
 * Added keep_PIC_vars, necessary for position independent code.
 * 
 * Revision 1.1  93/06/24  14:58:06  14:58:06  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


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


#ifdef __GNUC__
#ifdef __sun__
/* SunOS 4.1.3 doesn't have these in stdio.h */
extern int fputs PROTO_S((const char *, FILE*));
extern int fputc PROTO_S((int , FILE*));
extern int fprintf PROTO_W((FILE*,const char*, ...));
extern size_t fread PROTO_S((void*, size_t, size_t, FILE*));
extern int fflush PROTO_S((FILE *));
extern int fclose PROTO_S((FILE *));
extern int fgetc PROTO_S((FILE *));
extern int remove PROTO_S((const char *));
extern void setbuf PROTO_S((FILE *, char *));
#endif
#endif


/* Settings for SunOS 4 and Solaris 1 */
#define SYSV_ABI		0
#define SYSV_AS			0
#define DWARF			0
#define target_system		"SunOS 4.1.3"
#define ADDUNDERSCORE		1


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
#define DIV_SETS_CC 0

#define diagnose_registers 1

#define HAS_MAGIC 1

#define promote_pars 1

	/* condition for shape to be treated as a struct */
#define sparccpd(s) (name(s) == cpdhd || name(s) == nofhd || \
			name(s) == shcomplexhd || shape_size(s)>64 || \
			name(s) == u64hd || name(s) == s64hd)

#endif /* CONFIG_INCLUDED */



