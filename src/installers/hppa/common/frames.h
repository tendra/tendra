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
$Log: frames.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1996/09/05  11:05:10  wfs
 * "dynamic_init" boolean variable removed - must always be considered true.
 *
 * Revision 1.4  1996/01/30  15:36:28  wfs
 * Added the dynamic initialization files "dyn_begin.s" and "dyn_end.s" to
 * the hppatrans repository. The bl_install and bl_update scripts were
 * expanded to deal with these new "initcode" files.
 *
 * Revision 1.3  1996/01/19  14:13:18  wfs
 * Added "bool" type to an extern declaration in "frames.h".
 *
 * Revision 1.2  1995/12/18  13:11:20  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.2  1995/10/20  13:48:14  wfs
 * "set_up_frame()" and "setframe_flags()" declared for gcc compilation.
 *
 * Revision 5.1  1995/09/15  13:48:19  wfs
 * Variable name change.
 *
 * Revision 5.0  1995/08/25  13:55:56  wfs
 * Preperation for August 95 Glue release
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:01:26  wfs
 * Many of the frame specific variables are noew defined in "frames.c",
 * their external declarations have been moved to this header file"
 *
 * Revision 3.4  1995/08/25  11:01:26  wfs
 * Many of the frame specific variables are noew defined in "frames.c",
 * their external declarations have been moved to this header file"
 *
 * Revision 3.1  95/04/10  16:26:27  16:26:27  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:07  11:17:07  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:26:54  15:26:54  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:38:18  13:38:18  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef FRAMES
#define FRAMES

#include "common_types.h"
#include "addrtypes.h"

extern bool Has_fp;
extern bool Has_vsp;
extern bool Has_tos;
extern bool No_S;
extern bool Has_ll;
extern bool Has_checkalloc;
extern bool Has_vcallees;
extern bool Uses_crt_env;
extern bool Has_no_vcallers;
extern bool is_PIC_and_calls;
extern bool plusZ;

extern long callees_offset;
extern long params_offset;
extern long locals_offset;
extern long frame_sz;
extern long max_args;
extern long locals_space;
extern int fixdump;
extern int gdb,xdb,gcc_assembler;
extern long stackerr_lab,aritherr_lab;

extern baseoff MEM_TEMP_BOFF,LONG_RESULT_BOFF,SP_BOFF,FP_BOFF;

/* EXTENSION */ extern bool Has_vcallees;

extern long frame_offset PROTO_S (( exp id ));
extern void set_up_frame PROTO_S (( exp ));
extern void setframe_flags PROTO_S (( exp, bool ));

/* EXTENSION */ extern long callee_sz;

#endif













