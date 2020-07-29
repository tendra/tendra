/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/error.h>

#include <local/exp.h>

#include <tdf/tag.h>

#include <reader/basicread.h>

#include <utility/bits.h>

#include "procrec.h"
#include "bits.h"
#include "frames.h"

extern exp father(exp);
extern  procrec * procrecs;

bool Has_fp = 0;

bool Has_tos = 0;

bool No_S = 0;

bool Has_vcallees = 0;
bool Has_no_vcallers = 0;

int local_reg = 23;

long callee_size;


void setframe_flags
(exp e, bool leaf)
{
      /* e is proc_tag */

      No_S = (!leaf && (e->tag!=general_proc_tag || !proc_has_nolongj(e))
		&& proc_uses_crt_env(e)
      			&& proc_has_lv(e));
      Has_fp = (No_S || proc_has_alloca(e) || e->tag == general_proc_tag);

      Has_tos = (No_S && proc_has_alloca(e));
      Has_vcallees = (e->tag ==general_proc_tag && proc_has_vcallees(e));
      Has_no_vcallers = (e->tag == proc_tag || !proc_has_vcallers(e));

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
(exp e)
{
	procrec * pr = & procrecs[no(e)];
	needs * ndpr = & pr->needsproc;
	spacereq *sppr = & pr->spacereqproc;
	long pprops = (ndpr->propneeds);
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
	if (!leaf) {
	  pr->fixdump |= 1 << 31;
	}	/* space for link */

        if (Has_fp) {
		pr->fixdump &= ~(1<<30);
		/* frame pointer will be preserved by call or prelude ?!*/
        }

	pr->floatdump = (No_S)?0xffc00000 :((sppr->fltdump) << 20);

	nofixdump = bits_in(pr->fixdump);
	/* no of fixed s-regs to be dumped */
		ma += (nofixdump + bits_in(pr->floatdump))*32;
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
(exp id)
{
	exp p;
	procrec * pr;
	int  x = no(id);
    	int  b = x & 0x3f;
    	int lo; int fs; int cs;

	assert(id->tag == ident_tag);
	for (p = father(id);(p->tag!=proc_tag && p->tag!=
		general_proc_tag); p = father(p));
	pr = & procrecs[no(p)];

	lo = pr->locals_offset>>3;
	fs = pr->frame_size>>3;
	cs = pr->callee_size>>3;


	if (b==29 || b == 30) {
		return ((x - b) >> 4) +lo - (fs+cs);
	}
	else
	if (b==local_reg) {
	 	return ((x - b) >> 4) +lo -fs;
	}
	else {
		/* may not be allocated yet */

           bool Has_vcallees = (p->tag ==general_proc_tag &&
           					proc_has_vcallees(p));
           int n = no(son(id)) >>3;
           if (isparam(id) && son(id)->tag!=formal_callee_tag) {
           	return n;
           }
           else
	   if (isparam(id) && son(id)->tag ==formal_callee_tag) {
           	return (Has_vcallees)? n:(cs-n);
           }
           else { error(ERR_INTERNAL, "Wrong env_offset"); return 0; }
       }
}
