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
$Date: 1998/02/04 15:49:08 $
$Revision: 1.2 $
$Log: regexps.h,v $
 * Revision 1.2  1998/02/04  15:49:08  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:12  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef	REGEXPSDECS_H
#define	REGEXPSDECS_H	1

#include "memtdf.h"

/* number to add to floating point reg number for these functions */
#define	KEPT_FREG_OFFSET	32

extern void clear_all PROTO_S ((void));
extern void clear_reg PROTO_S ((int));
#define clear_freg(reg)		clear_reg((reg)+KEPT_FREG_OFFSET)

extern bool keep_eq_size PROTO_S ((shape, shape));

extern ans iskept PROTO_S ((exp));
extern ans iskept_reg PROTO_S ((exp));
extern ans iskept_freg PROTO_S ((exp));
extern ans iskept_inreg PROTO_S ((exp, int));

extern int ans_reg PROTO_S ((ans));

extern void keepexp PROTO_S ((exp, ans));
extern void keepcont PROTO_S ((exp, int));
extern void keepreg PROTO_S ((exp, int));

extern bool dependson PROTO_S ((exp, bool, exp));
extern void clear_dep_reg PROTO_S ((exp));

#endif
