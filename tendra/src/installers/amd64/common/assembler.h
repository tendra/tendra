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


/* 80x86/assembler.h */

/**********************************************************************
$Author: release $
$Date: 1998/03/16 11:25:20 $
$Revision: 1.2 $
$Log: assembler.h,v $
 * Revision 1.2  1998/03/16  11:25:20  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/10/10  18:24:51  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.4  1996/02/08  13:45:10  pwe
 * Linux elf v aout option
 *
 * Revision 1.3  1995/10/09  15:13:58  pwe
 * dynamic initialisation etc
 *
 * Revision 1.2  1995/01/30  12:55:55  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:00:36  jmf
 * Initial revision
 *
**********************************************************************/

#ifndef assembler_key
#define assembler_key 1


extern  void outbyte PROTO_S ((void));
extern  void outshort PROTO_S ((void));
extern  void outlong PROTO_S ((void));

extern  void align_label PROTO_S ((int f, exp jr));
extern  void eval_postlude PROTO_S ((char *s, exp c));
extern  void out_readonly_section PROTO_S ((void));
extern  void out_dot_comm PROTO_S ((char *id, shape sha));
extern  void out_dot_lcomm PROTO_S ((char *id, shape sha));
extern  void out_bss PROTO_S ((char *id, shape sha));

extern  void pic_prelude PROTO_S ((void));

extern  void out_switch_jump PROTO_S ((int tab, where a, int min));
extern  void out_switch_table PROTO_S ((int tab, int min, int max,
            int *v, int absent));

extern  void proc_size PROTO_S ((char *s));
extern  void proc_type PROTO_S ((char *s));
extern  void dot_align PROTO_S ((int n));
extern  void outend PROTO_S ((void));

extern  void outopenbr PROTO_S ((void));
extern  void outclosebr PROTO_S ((void));
extern  void outdivsym PROTO_S ((void));

extern void out_initialiser PROTO_S ((char *id));

#if islinux || isfreebsd
#if islinux
extern void set_linux_format PROTO_S ((int elf)); /* machine.c */
#endif
extern void out_main_prelude PROTO_S ((void));
extern void out_main_postlude PROTO_S ((void));
#endif


#endif
