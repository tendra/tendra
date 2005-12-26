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


/*****************************************************************
 *		eval.c
 *
 *	The main procedure defined here is evaluated which ouputs
 *assembler for data. The parameters are an evaluated exp and an index
 *into the table of externals (or 0 meaning anonymous). XXX
 *****************************************************************/

#include "config.h"
#include "common_types.h"
#include "addrtypes.h"
#include "tags.h"
#include "exp.h"
#include "exptypes.h"
#include "maxminmacs.h"
#include "shapemacs.h"
#include "flpttypes.h"
#include "flpt.h"
#include "syms.h"
#include "out_ba.h"
#include "main.h"
#include "ibinasm.h"
#include "frames.h"
#include "procrectypes.h"
#include "f64.h"
#include "eval.h"
#include "basicread.h"

extern void globalise_name(dec*);
extern  procrec * procrecs;

long  G_number = 64;		/* to give choice of .sdata or data */

int   data_lab = 33;

int
next_data_lab()
{	/*  anonymous label in data space - $$n in assembler o/p */
	return data_lab++;
}

int
next_dlab_sym()
{	/* as above - but also gives it a symno for .G output */
	symnofordata (data_lab);
	return data_lab++;
}


/* various pieces of info for outputting data depending on shape */
mm scmm = {
	127, -128, "\t.byte %ld :%ld\n"
};
mm uscmm = {
	255, 0, "\t.byte %ld :%ld\n"
};
mm shmm = {
	0x7fff, 0xffff8000, "\t.half %ld :%ld\n"
};
mm ushmm = {
	0xffff, 0, "\t.half %ld :%ld\n"
};
mm swmm = {
	0x7fffffff, 0x80000000, "\t.word %ld :%ld\n"
};
mm uswmm = {
	0xffffffff, 0, "\t.word %ld :%ld\n"
};

/*************************************************************
 *maxmin
 *
 *finds the data size from the range of an integer shape
 **************************************************************/
mm
maxmin(shape s)
{
	switch (name (s)) {
    case scharhd:
		return scmm;
    case ucharhd:
		return uscmm;
    case swordhd:
		return shmm;
    case uwordhd:
		return ushmm;
    case slonghd:
		return swmm;
    case ulonghd:
		return uswmm;
    default: {
		
		return uswmm;
	}
	}
	
}


/**************************************************************
 *outlab
 *
 *outputs the label parameter if non negative else interprets it
 *to be an index into the externals and outputs the identifier.
 **************************************************************/

void
outlab(int l)
{
	if (l >= 0) {
		fprintf (as_file, "$$%d", l);
	}
	else {
		char *extname = main_globals[-l - 1] -> dec_u.dec_val.dec_id;
		fprintf (as_file, "%s", extname);
	}
}





/***************************************************************
 *evalone
 *
 *This procedure outputs all non-pack expressions and puts in label
 *values for the pack exps (putting new label numbers into their number
 *fields) which it accumulates for later application in the ptr parameter
 *of evalone. This is done to cope with the fact that the exp to evaluated
 *may contain pack operations which are graph-like .
 ***************************************************************/
long
evalexp(exp e)
{
	switch (name(e)) {
    case  val_tag: case null_tag: case top_tag:{
		if (name(sh(e)) == offsethd && al2(sh(e)) >= 8) {
			return (no(e)>>3);
		}
        return (no (e));
    }
    case bitf_to_int_tag:
	{
		return evalexp (son (e));
	}
    case int_to_bitf_tag:
	{
		ash a;
		long  w = evalexp (son (e));
		a = ashof (sh (e));
		if (a.ashalign != 1) {
			failer ("should be align 1");
		}
		if (a.ashsize != 32) {
			w &= ((1 << a.ashsize) - 1);
		}
		return w;
	}
    case not_tag:
	{
		return (~evalexp (son (e)));
	}
    case and_tag:
	{
		return (evalexp (son (e)) & evalexp (bro (son (e))));
	}
    case or_tag:
	{
		return (evalexp (son (e)) | evalexp (bro (son (e))));
	}
    case xor_tag:
	{
		return (evalexp (son (e)) ^ evalexp (bro (son (e))));
	}
	
    case shr_tag:
	{
		return (evalexp (son (e)) >> evalexp (bro (son (e))));
	}
	
    case shl_tag:
	{
		return (evalexp (son (e)) << evalexp (bro (son (e))));
	}
	
    case concatnof_tag:
	{
		ash a;
		long  wd = evalexp (son (e));
		a = ashof (sh (son (e)));
		return (wd | (evalexp (bro (son (e))) << a.ashsize));
	}
	
    case clear_tag:
	{
		ash a;
		a = ashof (sh (e));
		if (a.ashsize > 32)
			failer ("clearshape");
		return 0;
	}
	case env_offset_tag:
	case general_env_offset_tag: {
		return frame_offset(son(e));
	}
	case env_size_tag: {
		exp tg = son(son(e));
		procrec * pr = &procrecs[no(son(tg))];
		return ((pr->frame_size+pr->callee_size) >> 3);
	}
	case offset_add_tag:{
    	return (evalexp(son(e))+evalexp(bro(son(e))));
	}
	case offset_max_tag:{
    	return (max(evalexp(son(e)),evalexp(bro(son(e)))));
	}
	case offset_pad_tag:{
		return (rounder(evalexp(son(e)), shape_align(sh(e))));
	}
	case offset_mult_tag:{
    	return (evalexp(son(e))*evalexp(bro(son(e))));
	}
	case offset_div_tag:case offset_div_by_int_tag:{
    	return (evalexp(son(e))/evalexp(bro(son(e))));
	}
	case offset_subtract_tag:{
    	return (evalexp(son(e))-evalexp(bro(son(e))));
	}
	case offset_negate_tag: {
		return (- evalexp(son(e)));
	}
    default:
		failer ("tag not in evalexp");
	}
	return 0;
}

void
set_align(int al)
{
	if (al<16) return;
	if (as_file)
		fprintf (as_file, "\t.align%s\n",
				 (al == 16) ? " 1" :
				 ((al == 32) ? " 2" :
				  ((al == 64) ? " 3" : " 0")));
	out_value (0, ialign, (al == 16) ? 1 :
			   ((al == 32) ? 2 :
				((al == 64) ? 3 : 0)), 0);
	
}

int
eval_al(shape s)
{
	if (shape_align(s)!=1) return shape_align(s);
	if (shape_size(s) <=8) return 8;
	if (shape_size(s) <=16) return 16;
	return 32;
}

void
oneval(int val, int al, int rep)
{
	char *as = (al <= 8) ? "\t.byte %ld :%ld\n"
		:     ((al <= 16) ? "\t.half %ld :%ld\n"
			   :     "\t.word %ld :%ld\n");
	set_align(al);
	if (as_file)
		fprintf (as_file, as, val, rep);
	out_value (0, (al <= 8) ? ibyte : ((al <= 16) ? ihalf : iword), val, rep);
}



void
evalone(exp e, long rep)
{
	/* outputs constant expression e, rep
	 *				   times;  */
	ash a;
	a = ashof (sh (e));
	switch (name (e)) {
		
    case string_tag:
	{
        long char_size = props(e);
		long  strsize = shape_size(sh(e))/char_size;
		char *st = nostr(e);
		long  strs = shape_size(sh(e))>>3;
		int   i,j;
		if (rep != 1 && as_file)
			fprintf (as_file, "\t.repeat %ld\n", rep);
		set_align(char_size);
		if (as_file) {
			for (j=0; j< strsize;) {
				switch (char_size) {
				case 8: fprintf (as_file, "\t.byte "); break;
				case 16: fprintf (as_file, "\t.half "); break;
				case 32: fprintf (as_file, "\t.word "); break;
				}
				for (i = j; i < strsize && i-j < 8; i++) {
					switch (char_size) {
					case 8:fprintf (as_file, "0x%x ", st[i]); break;
					case 16:fprintf (as_file, "0x%x ", ((short *)st)[i]); break;
					case 32:fprintf (as_file, "0x%lx ", ((long *)st)[i]); break;
					}
				}
				j =i;
				fprintf (as_file, "\n");
			}
		}
		if (rep != 1 && as_file)
			fprintf (as_file, "\t.endr\n");
		out_chars (0, iascii, strs, rep);
		out_data (st, strs);
		return;
	}
    case real_tag:
	{
		r2l   n;
		int i;
		n = real2longs_IEEE(&flptnos[no (e)], (a.ashsize>32)?1:0);
		set_align(a.ashalign);
		for (i=0; i<rep; i++) {
			if (BIGEND) {
				if (a.ashsize>32)  oneval(n.i2, 32, 1);
				oneval(n.i1, 32, 1);
			}
			else {
				oneval(n.i1, 32, 1);
          		if (a.ashsize>32) oneval(n.i2, 32, 1);
			}
        }
		return;
	}
    case null_tag: case top_tag:
		no (e) = 0;
    case val_tag:
	{
		if (shape_size(sh(e)) > 32) {
			flt64 temp;
			int ov;
			int i;
			if (isbigval(e)) {
				temp = flt_to_f64(no(e), 0, &ov);
			}
			else {
				temp.big = (is_signed(sh(e)) && no(e)<0)?-1:0;
				temp.small = no(e);
			}
			for (i=0; i<rep; i++) {
				oneval(temp.small, 32, 1);
				oneval(temp.big, 32, 1);
			}
			return;
		}
		
		oneval(evalexp(e), eval_al(sh(e)), rep);
		return;
	}
	
    case name_tag:
	{
		exp dc = son(e);
		dec * globdec= brog(dc);/* must be global name */
		char *nm = globdec -> dec_u.dec_val.dec_id;
		long symdef = globdec ->dec_u.dec_val.sym_number;
		if (!isvar(dc) && son(dc) != nilexp
			&& name(son(dc)) != proc_tag && name(son(dc)) != general_proc_tag
			&& no(e)==0
			&& shape_size(sh(e)) == shape_size(sh(son(dc))) ) {
			evalone(son(dc), rep);
			return;
		}
		set_align(32);
		if (as_file) {
			if (no (e) == 0) {
				fprintf (as_file, "\t.word %s : %ld\n", nm, rep);
			}
			else {
				fprintf (as_file, "\t.word %s + %d :%ld\n", nm, no (e) / 8, rep);
			}
		}
		out_value (symnos[symdef], iword, no (e) / 8, rep);
		return;
	}
    case compound_tag:  {
		exp tup = son (e);
		unsigned long val;
		bool first_bits=1;
		long bits_start =0;
		long offs =0;
		
		if (rep != 1)
			failer ("CAN'T REP TUPLES");
		set_align(a.ashalign);
		
		
		for (;;) {
			ash ae;
			ae = ashof(sh(bro(tup)));
			offs = no(tup);
			if (ae.ashalign == 1) {
				unsigned long vb = evalexp(bro(tup));
				if (ae.ashsize != 32) {
					vb = vb & ((1<<ae.ashsize)-1);
				}
                if (first_bits) {
					val = 0;
					first_bits=0;
                }
				
                if (offs - bits_start +ae.ashsize > 32) {
					if (BIGEND) {
						for (;;) {
							oneval(val>>24, 8, 1);
							val <<=8;
							bits_start+=8;
							if (offs-bits_start < 8) break;
						}
					}
					else {
						for (;;) {
							oneval(val &255, 8,1);
							val >>= 8;
							bits_start += 8;
							if (offs - bits_start  < 8)
								break;
						}
					}
                }
				
                if (offs - bits_start +ae.ashsize <= 32) {
					if (BIGEND) {
						val |= (vb << (32 -offs+bits_start-ae.ashsize));
					}
					else {
                     	val |= (vb <<(offs-bits_start));
					}
                }
                else {
					failer("Constant bitfield does not fit into 32 bits");
                }
			}
			else {
				if (!first_bits) {
					first_bits=1;
					if (BIGEND) {
						for (;;) {
							oneval(val>>24, 8, 1);
							val <<=8;
							bits_start+=8;
							if (offs-bits_start <= 0) break;
						}
					}
					else {
						for (;;) {
							oneval(val &255, 8,1);
							val >>=8;
							bits_start += 8;
							if (offs - bits_start  <=0)
								break;
						}
					}
				}
				while (bits_start < offs) {
					oneval(0, 0, 1);
					bits_start+=8;
				}
				evalone(bro(tup),1);
				bits_start += shape_size(sh(bro(tup)));
			}
			
			if (last(bro(tup))) {
				offs += ae.ashsize;
				offs = (offs+7)&~7;
				for (;!first_bits;) {
					if (BIGEND) {
						oneval(val>>24, 8, 1);
						val <<=8;
						bits_start+=8;
						if (offs-bits_start<= 0) break;
					}
					else {
						oneval(val &255, 8,1);
						val >>= 8;
						bits_start +=8;
						if (offs - bits_start <=0)
							break;
					}
				}
				Assert(a.ashsize >= offs);
				while (a.ashsize > offs) { /* pad out unions etc */
					oneval(0,8,1);
					offs+=8;
				}
				return;
			}
			tup = bro(bro(tup));
		}
		
	}
		
	case nof_tag: {
		exp s = son(e);
		if (s==nilexp) return;
		if (rep != 1)
			failer ("CAN'T REP TUPLES");
		set_align(a.ashalign);
		for (;;) {
			evalone(s,1);
			if (last(s)) return;
			s = bro(s);
		}
	}
		
		
    case ncopies_tag:
	{
        if (name(son(e)) == compound_tag || name(son(e)) == concatnof_tag ||
			name(son(e)) == nof_tag) {
			int n;
			for (n = rep*no(e); n > 0; n--) {
             	evalone(son(e), 1);
			}
        }
		else evalone (son (e), rep * no (e));
		return;
	}
	
    case concatnof_tag:
	{
		if (a.ashalign == 1) {
			long  ee = evalexp (e);
			exp dad = father(e);
			ash abits;
			abits = ashof(sh(dad));
			oneval(ee, abits.ashalign, rep);
		}
		else {
			if (rep != 1)
				failer ("CAN'T REP concat");
			evalone (son (e), 1);
			evalone (bro (son (e)), 1);
		}
		return;
	}
	
    case clear_tag:
	{
		int s = eval_al(sh(e));
		if (as_file)
			fprintf (as_file, "\t.space %ld\n", (s>>3) * rep);
		out_value (0, ispace, (s>>3) * rep, 1);
		return;
	}
	
	
	
    case not_tag:
    case and_tag:
    case or_tag:
    case shl_tag:
    case shr_tag:
    case bitf_to_int_tag:
    case int_to_bitf_tag:
    case env_offset_tag:
    case general_env_offset_tag:
	case env_size_tag: case offset_add_tag: case offset_max_tag:
	case offset_pad_tag: case offset_mult_tag: case offset_div_tag:
	case offset_div_by_int_tag: case offset_subtract_tag: case offset_negate_tag:
	{
		long  ee = evalexp (e);
		oneval(ee, eval_al(sh(e)) , rep);
		return;
	}
	case seq_tag:
	{
		if (name(son(son(e))) == prof_tag && last(son(son(e))))
		{ evalone(bro(son(e)),rep); return;}
	}		/* otherwise drop through to failure */
	
	
    default:
		failer ("tag not in evaluated");
		
	}				/* end switch */
}


/*****************************************************************
 *evaluated
 *
 *This outputs data from the evaluated exp into either .sdata or .data
 *depending on size and labels this data either with either id in main_globals
 *or an anonymous label derived from l. The result is the instore "address"
 *of the constant. A negative l implies that this is the initialisation of a global
 *variable.

*****************************************************************/

instore
evaluated(exp e, long l, dec * dc)
{
	
	int   lab = (l == 0) ? next_dlab_sym ()
		: (l< 0)? l: -l;
	int   lab0 = lab;
	ash a;
	instore isa;
	exp z = e;
	
	isa.adval = 0;
	isa.b.offset = 0;
	isa.b.base = lab0;
	
	
	if (name (e) == clear_tag) {/* uninitialised global */
		int   size = (ashof (sh (e)).ashsize + 7) >> 3;
		bool temp = (l == 0 ||
					 (main_globals[-lab - 1] -> dec_u.dec_val.dec_id)[0] == '$');
		if (dc != (dec*)0) globalise_name(dc);
		if (as_file) {
			fprintf (as_file, (temp) ? "\t.lcomm\t" : "\t.comm\t");
			outlab (lab);
			fprintf (as_file, " %d\n", size);
		}
		out_value ((lab >= 0) ? tempsnos[lab - 32] : symnos[-lab - 1],
				   (temp) ? ilcomm : icomm, size, 1);
		
		return isa;
	}
	
	
    a = ashof (sh (z));
    if (a.ashsize <= G_number) {
		if (as_file)
			fprintf (as_file, "\t.sdata\n");
		out_common (0, isdata);
    }
    else {
		if (as_file)
			fprintf (as_file, "\t.data\n");
		out_common (0, idata);
    }
    set_align(a.ashalign);   /* I think this is unnecessary ? bug in as */
    if (dc != (dec*)0) globalise_name(dc);
    if (as_file) {
		outlab (lab);
		fprintf (as_file, ":\n");
    }
    out_common ((lab > 0) ? tempsnos[lab - 32] : symnos[-lab - 1], ilabel);
    evalone (z, 1);
	
	return isa;
}
