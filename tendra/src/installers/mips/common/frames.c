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
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: frames.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1995/09/26  09:05:02  currie
 * Has_no_vcallers condition wrong
 *
 * Revision 1.4  1995/09/12  10:59:21  currie
 * gcc pedanttry
 *
 * Revision 1.3  1995/06/28  12:15:22  currie
 * New make_stack_limit etc
 *
 * Revision 1.2  1995/05/05  08:12:52  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/

#include "config.h"
#include "common_types.h"
#include "procrectypes.h"
#include "expmacs.h"
#include "tags.h"
#include "bitsmacs.h"
#include "basicread.h"
#include "frames.h"
#include "new_code.h"

extern exp father PROTO_S ((exp));
extern  procrec * procrecs;

bool Has_fp = 0;

bool Has_tos = 0;

bool No_S = 0;

bool Has_vcallees = 0;
bool Has_no_vcallers = 0;

int local_reg = 23;

long callee_size;


void setframe_flags
    PROTO_N ( (e, leaf) )
    PROTO_T ( exp e X bool leaf )
{
      /* e is proc_tag */

      No_S = (!leaf && (name(e)!=general_proc_tag || !proc_has_nolongj(e))
		&& proc_uses_crt_env(e)
      			&& proc_has_lv(e) );
      Has_fp = (No_S || proc_has_alloca(e) || name(e) == general_proc_tag);

      Has_tos = (No_S && proc_has_alloca(e));
      Has_vcallees = (name(e)==general_proc_tag && proc_has_vcallees(e));
      Has_no_vcallers = (name(e) == proc_tag || !proc_has_vcallers(e));

#ifdef Try_No_S
	No_S = 1;
#endif
#ifdef Try_Has_fp
	Has_fp = !leaf;
#endif
#ifdef Try_Has_tos
	Has_tos = 1;
#endif
}

void setframe_info
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
	procrec * pr = & procrecs[no(e)];
	needs * ndpr = & pr->needsproc;
	spacereq *sppr = & pr->spacereqproc;
	long pprops = (ndpr->propsneeds);
	bool leaf = (pprops & anyproccall) == 0;
	long ma = ndpr->maxargs;	/* maxargs of proc body in bits */
	long st = sppr->stack;	/* space for locals in bits */
	int nofixdump;

	setframe_flags(e, leaf);

	if (!leaf && ma <128) ma = 128;	/* required by printf etc!!?? */
	st = (st + 32) & ~63;
	ma = (ma + 32) & ~63;	/* put on 64 bit boundaries */

	pr->max_args = ma;

	pr->fixdump = (No_S)?0x40ff0000 :((sppr->fixdump) << 16);
	if (!leaf ) {
	  pr->fixdump |= 1 << 31;
	}	/* space for link */

        if (Has_fp) {
		pr->fixdump &= ~(1<<30);
		/* frame pointer will be preserved by call or prelude ?!*/
        }

	pr->floatdump = (No_S)?0xffc00000 :((sppr->fltdump) << 20);

	nofixdump = bitsin (pr->fixdump);
	/* no of fixed s-regs to be dumped */
		ma += (nofixdump + bitsin(pr->floatdump))*32;
	ma = (ma + 32) & ~63;
	/* include space for dumped s-regs */

	pr->locals_offset = ma;	/* the offset to first local in bits from
				   $sp */
	pr->frame_size = ma + st;	/* the frame size for this proc in bits */


	st = pr->frame_size >> 3;
	ma = ma >> 3;
	pr->dumpstart = ma;		/* the byte displacement from $sp to dump
				   fixed s-regs */
	pr->fldumpstart = ma - 4 * nofixdump;
	/* the byte displacement from $sp to dump float s-regs... */

}

long frame_offset
    PROTO_N ( (id) )
    PROTO_T ( exp id )
{
	exp p;
	procrec * pr;
	int  x = no (id);
    	int  b = x & 0x3f;
    	int lo; int fs; int cs;

	Assert(name(id) == ident_tag);
	for (p = father(id); (name(p)!=proc_tag && name(p) !=
		general_proc_tag); p = father(p));
	pr = & procrecs[no(p)];

	lo = pr->locals_offset>>3;
	fs = pr->frame_size>>3;
	cs = pr->callee_size>>3;


	if (b==29 || b == 30) {
		return ( ((x - b) >> 4) +lo -(fs+cs));
	}
	else
	if (b==local_reg) {
	 	return ( ((x - b) >> 4) +lo -fs);
	}
	else {
		/* may not be allocated yet */

           bool Has_vcallees = (name(p)==general_proc_tag &&
           					proc_has_vcallees(p));
           int n = no(son(id))>>3;
           if (isparam(id) && name(son(id))!=formal_callee_tag) {
           	return n;
           }
           else
	   if (isparam(id) && name(son(id))==formal_callee_tag) {
           	return  ((Has_vcallees)? n:(cs-n));
           }
           else { failer("Wrong env_offset"); return 0; }
       }
}
