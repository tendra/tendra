/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:44 $
$Revision: 1.2 $
$Log: error.h,v $
 * Revision 1.2  1998/02/04  15:48:44  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:28  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef ERROR_H
#define ERROR_H
extern void init_proc_errors PROTO_S ((exp));
extern void output_error_labels PROTO_S ((void));
extern long get_nil_access_lab PROTO_S ((void));
extern long get_overflow_lab PROTO_S ((void));
extern long get_stack_overflow_lab PROTO_S ((void));

/* integer error treatments */
extern int abs_error_treatment PROTO_S ((exp,space,where));
extern int chvar_error_treatment PROTO_S ((exp,space,where));
extern void div_error_treatment PROTO_S ((int,int,exp));
extern int minus_error_treatment PROTO_S ((exp,space,where));
extern int mult_error_treatment PROTO_S ((exp,space,where));
extern int neg_error_treatment PROTO_S ((exp,space,where));
extern int plus_error_treatment PROTO_S ((exp,space,where));
extern void rem_error_treatment PROTO_S ((int,int,exp));
extern void round_error_treatment PROTO_S ((exp *));

/* floating error treatments */
extern void chfl_error_treatment PROTO_S ((exp,int));
extern void do_fmop_error_jump PROTO_S ((exp,int,int));
extern void do_fop_error_jump PROTO_S ((exp,int,int,int));
extern void do_trap PROTO_S ((exp));

/* macros */
#define NO_ERROR_TREATMENT(x) (optop(x)!=0)
#define ERROR_TREATMENT(x) (optop(x)==0)
#define ERROR_TREATMENT_IS_TRAP(x) ((errhandle(x)&3)==3)
#endif
