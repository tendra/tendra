/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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
 *	(1) Its Recipients shall ensure that this Notice is
 *	reproduced upon any copies or amended versions of it;
 *    
 *	(2) Any amended version of it shall be clearly marked to
 *	show both the nature of and the organisation responsible
 *	for the relevant amendment or amendments;
 *    
 *	(3) Its onward transfer from a recipient to another
 *	party shall be deemed to be that party's acceptance of
 *	these conditions;
 *    
 *	(4) DERA gives no warranty or assurance as to its
 *	quality or suitability for any purpose and DERA accepts
 *	no liability whatsoever in relation to any use to which
 *	it may be put.
 *
 * $TenDRA$
 */


/**/


#define HPPATRANS_CODE
/******************************************************************
 *		code_here
 *
 *This contains procedures :-
 *
 *regofval, fregofval : to see if an exp is a load_tag that has been allocated to a register.
 *
 *regoperand, freoperand : to evaluate an exp into a register using make_code
 *
 *code_here :  calls make_code and ensures that any internal exit labels are tied up after the call
 *
 *
 *	The procedures regoperand and fregoperand evaluate their
 *exp parameter into a single register using make_code. This register is
 *returned. An initial test with regofval checks to see if the exp is already
 *in a register.

******************************************************************/


#include "config.h"
#include "myassert.h"
#include "common_types.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "labels.h"
#include "expmacs.h"
#include "tags.h"
#include "makecode.h"
#include "exp.h"
#include "bitsmacs.h"
#include "locate.h"
#include "regexps.h"
#include "regmacs.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "shapemacs.h"
#include "special.h"
#include "regable.h"
#include "guard.h"
#include "move.h"
#include "comment.h"

#include "codehere.h"


/*********************************************************************
 *regofval
 *The procedure regofval checks to see if an exp is a load_tag
 *that has been allocated into a fixpnt register and if so return it or else R_NO_REG.
 *********************************************************************/
int
regofval(exp e)
{
	exp dc = son(e);
	
	if (name(e) == name_tag && name(dc) == ident_tag)	/* ident tag */
	{
		if ((props(dc) & defer_bit) != 0)
		{
			return regofval(son(dc));
		}
		if ((props(dc) & inreg_bits) != 0)
		{
			return ((isvar(dc)) ? (-no(dc)) : (no(dc)));
		}
		return R_NO_REG;
	}
	else if ((name(e) == val_tag && no(e) == 0) 
#if 0
			 || name(e) == clear_tag || name(e)== top_tag 
#endif
		)
	{
		return 0;
	}
	else
	{
		return R_NO_REG;
	}
}

int
fregofval(exp e)
{
	exp dc = son(e);
	
	if (name(e) == name_tag && name(dc) == ident_tag)
	{
		if ((props(dc) & infreg_bits) != 0)
		{
			return no(dc);
		}
		return R_NO_REG;
	}
	else
	{
		return R_NO_REG;
	}
}


/* calls make_code and tie up any internal exit labels */
static int
make_code_here(exp e, space sp, where dest)
{
	makeans mka;
	
	mka = make_code(e, sp, dest, 0);
	if (mka.lab != 0)
	{
		clear_all();
		outlab("L$$",mka.lab);
	}
	return mka.regmove;
}


/* return reg if 'e' e can easily go to one reg only */
static int
is_reg_operand(exp e, space sp)
{
	int x = regofval(e);
	ans aa;
	
	if (x >= 0 && x < R_NO_REG)
		return x;			/* x is a register for e */
	
	if (name(e) == cont_tag)
	{
		x = regofval(son(e));
		if (x < 0)
			return (-x);
	}
	
	aa = iskept(e);
	
	if (discrim (aa) == inreg && regalt(aa) != 0)
	{				/* the same expression has already been
					 * evaluated into a reg */
		return regalt(aa);
	}
	
	if (discrim (aa) == notinreg)
	{
		instore is;
		
		is = insalt(aa);
		if (is.adval && is.b.offset == 0)
		{
			int r = is.b.base;
			
			/* the same expression has already been evaluated into a reg */
			return r;
		}
	}
	
	return R_NO_REG;		/* exprssion can go to many regs just as
							 * easily */
}


int
reg_operand(exp e, space sp)
{
	int reg;
	
	reg = is_reg_operand(e, sp);
	
	if (reg == R_NO_REG || reg == GR0)
	{
		/* allow make_code_here to evaluate e into reg of its choice */
		ans aa;
		where w;
		
		reg = -1;
		setsomeregalt(aa, &reg);
		w.answhere = aa;
		w.ashwhere = ashof(sh(e));
		make_code_here(e, sp, w);
		assert(reg!=-1);
		keepreg(e, reg);
		return reg;
	}
	else
	{
		/* e was found easily in a reg */
		assert(IS_FIXREG(reg));
		return reg;
	}
}

/* like reg_operand(), but to specified reg */
void
reg_operand_here(exp e, space sp, int this_reg)
{
	int reg;
	
	assert(IS_FIXREG(this_reg) && this_reg != GR0);	/* variable fix reg */
	
	
	reg = is_reg_operand(e, sp);
	
	if (reg == R_NO_REG || reg == GR0)
	{
		/* evaluate to this_reg */
		
		where w;
		
		w.ashwhere = ashof(sh(e));
		setregalt(w.answhere, this_reg);
		make_code_here(e, sp, w);
	}
	else
	{
		/* e was found easily in a reg, move to this_reg if needed */
		assert(IS_FIXREG(reg));
		
		if (reg != this_reg)
			rr_ins(i_copy,reg,this_reg);
	}
	
	keepreg(e, this_reg);
}


int
freg_operand(exp e, space sp, int reg)
{
	int x = fregofval(e);
	ans aa;
	where w;
	freg fr;
	
	w.ashwhere = ashof(sh(e));
	fr.dble = (w.ashwhere.ashsize == 64) ? 1 : 0;
	
	if (x >= 0 && x < R_NO_REG)
	{
		return x;
	}
	
	if (name(e) == cont_tag)
	{
		x = fregofval(son(e));
		if (x < R_NO_REG)
		{
			return (x);
		}
	}
	else if (name(e) == apply_tag)
	{
		fr.fr = R_FR4;
		setfregalt(aa, fr);
		comment("freg_operand: call of float point result proc");
		w.answhere = aa;
		/* w.ashwhere already correctly set up above */
		make_code(e, sp, w, 0);
		return R_FR4;   /* float point proc calls give result in %fr4 */
	}
	
	aa = iskept(e);
	if (discrim (aa) == infreg)
	{
		/* e already evaluated in fl reg */
		return regalt(aa) /* cheat */;
	}
	
	fr.fr = reg;
	setfregalt(aa, fr);
	w.answhere = aa;
	make_code_here(e, sp, w);
	keepexp(e, aa);
	return reg;
}



/*
 * The procedure code_here calls make_code and ensures that
 * any internal exit labels are tied up after the call.
 * Optimises the case where the value of 'e' is in a register.
 */
int
code_here(exp e, space sp, where dest)
{
	int reg;
	
	
	reg = is_reg_operand(e, sp);
	
	
	if (reg == R_NO_REG || reg == GR0)
	{
		return make_code_here(e, sp, dest);
	}
	else
	{
		/* +++ do in make_code maybe */
		/* +++ for reals as well */
		/* e was found easily in a reg */
		ans aa;
		
		assert(IS_FIXREG(reg));
		assert(ashof(sh(e)).ashsize <= 32);
		
		setregalt(aa, reg);
		move(aa, dest, guardreg(reg, sp).fixed, 1);
		
		return reg;
	}
}


















