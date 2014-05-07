/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>

#include <local/expmacs.h>
#include <local/szs_als.h>

#include <reader/codetypes.h>
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>
#include <reader/c_arith_type.h>
#include <reader/natmacs.h>
#include <reader/spec_tok.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/flags.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <diag/diag_fns.h>

#include <refactor/refactor.h>


/* intercepts specially defined tokens */

tokval
special_token(token t, bitstream pars, int sortcode, int * done)
{
  tokval tkv;
  UNUSED(sortcode);

  if (t -> tok_name == (char*)0) {
    SET(tkv); /* call looks at done to see if result is meaningful */
    return tkv;

  };

  if (builtin & BUILTIN_VARARG) {
    if (!strcmp(t -> tok_name,"ansi.stdarg.__va_start")) {
  	exp arg1;
  	exp id;
  	exp env_o;
  	place old_place;
  	old_place = keep_place();
  	set_place(pars);
  	arg1 = hold_refactor(d_exp());
  	set_place(old_place);
  	if (name(arg1) != name_tag) failer("Not a tag in va_start");
  	id = son(arg1);
  
  	env_o = getexp(f_offset(frame_alignment, f_alignment(sh(arg1))),
  			nilexp, 0, id, nilexp, 0, 0, env_offset_tag);
  	setvis(id);
  	setenvoff(id);
  	tkv.tk_exp = hold_refactor(f_add_to_ptr(f_add_to_ptr(f_current_env(), env_o),f_shape_offset(sh(arg1))));
  	kill_exp(arg1,arg1);
  	*done = 1;
  	return tkv;
    }
  }

  /* TODO: BUILTIN_? */ {
    if (!strcmp(t -> tok_name,"~next_caller_offset")) {
        exp arg1, arg2;
        shape sha1, sha2, sha3;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        arg1 = hold_refactor(d_exp());
        sha1 = d_shape();
        sha2 = d_shape();
        set_place(old_place);
        sha3 = (shape_size(sha2)>64 ? f_pointer(f_alignment(sha2)) :
  				    (shape_size(sha2)<32 ? swordsh : sha2));
        arg2 = hold_refactor(f_offset_pad(f_parameter_alignment(sha3),
  				     f_shape_offset(sha3)));
        if ((shape_size(sha1)<=32 || shape_size(sha1)>64) &&                              shape_size(sha3)==64)
        {
  	 arg1 = hold_refactor(f_offset_pad(f_parameter_alignment(realsh),arg1));
        }
        tkv.tk_exp = hold_refactor(me_b3(f_offset(al1_of(sh(arg1)),
  				             al2_of(sh(arg2))),
  				    arg1,arg2,offset_subtract_tag));
        *done = 1; 
  
        if (shape_size(sha2)>64)
        { 
  	 al2_of(sh(tkv.tk_exp))->al.sh_hd = nofhd+1;
        }
  
        return tkv;
    }
  
    if (!strcmp(t -> tok_name,"~next_callee_offset")) {
        exp arg1, arg2, off;
        shape sha1, sha2;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        arg1 = hold_refactor(d_exp());
        sha1 = d_shape();
        sha2 = d_shape();
        set_place(old_place);
        arg2 = hold_refactor(f_offset_pad(f_parameter_alignment(sha1),
  				     f_shape_offset(sha1)));
        off = hold_refactor(me_b3(f_offset(al1_of(sh(arg1)),
  				      al2_of(sh(arg2))),
  			     arg1,arg2,offset_add_tag));
        if (shape_align(sha1) < shape_align(sha2))
        {
  	 tkv.tk_exp = hold_refactor(f_offset_pad(f_parameter_alignment(sha2),off));
        }
        else
        {
  	 tkv.tk_exp = off;
        }
        *done = 1;
        return tkv;
    }
  }

  if (builtin & BUILTIN_ALLOCA) {
    if (!strcmp(t -> tok_name,"~alloc_size")) {
        exp off,off1,arg1;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        arg1 = hold_refactor(d_exp());
        set_place(old_place);
        off1 = hold_refactor(f_offset_pad(SLONG_ALIGN,arg1));
        off = hold_refactor(me_b3(f_offset(al1_of(sh(off1)),
  				      SLONG_ALIGN),
  			     off1,f_shape_offset(slongsh),offset_add_tag));
        tkv.tk_exp = hold_refactor(f_offset_pad(const_al512,off));
        *done = 1;
        return tkv;
    }
  
    if (!strcmp(t -> tok_name, "~alloca"))  {
        exp arg1;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        arg1 = hold_refactor(d_exp());
        set_place(old_place);
        tkv.tk_exp = hold_refactor(me_u3(f_pointer(long_to_al(8)),
  			   arg1, alloca_tag));
        *done = 1;
        has_alloca = 1;
        return tkv;
    };
  }

  if (builtin & BUILTIN_DIAG) {
    if (!strcmp(t -> tok_name, "~exp_to_source") ||
        !strcmp(t -> tok_name, "~diag_id_scope") ||
        !strcmp(t -> tok_name, "~diag_type_scope") ||
        !strcmp(t -> tok_name, "~diag_tag_scope"))  {
  
        place old_place;
        old_place = keep_place();
        set_place(pars);
        tkv.tk_exp = hold_refactor(d_exp());
        *done = 1;
  
        if (diag == DIAG_NONE)
  	{
  	  set_place(old_place);
  	  return tkv;
  	};
  
       if (!strcmp(t -> tok_name, "~exp_to_source"))
         {exp r;
  	diag_info * di = read_exp_to_source();
  	crt_lno = natint(di -> data.source.end.line_no);
  	crt_charno = natint(di -> data.source.end.char_off);
  	crt_flnm = di -> data.source.beg.file->file.ints.chars;
  	r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		   1, 0, diagnose_tag);
  	setfather(r, tkv.tk_exp);
  	dno(r) = di;
  	tkv.tk_exp = r;
  	set_place(old_place);
  	return tkv;
         };
  
       if (!strcmp(t -> tok_name, "~diag_id_scope"))
         {exp r;
  	diag_info * di = read_diag_id_scope();
  	r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		   2, 0, diagnose_tag);
  	setfather(r, tkv.tk_exp);
  	dno(r) = di;
  	tkv.tk_exp = r;
  	set_place(old_place);
  	return tkv;
         };
  
       if (!strcmp(t -> tok_name, "~diag_type_scope"))
         {exp r;
  	diag_info * di = read_diag_type_scope();
  	r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		   3, 0, diagnose_tag);
  	setfather(r, tkv.tk_exp);
  	dno(r) = di;
  	tkv.tk_exp = r;
  	set_place(old_place);
  	return tkv;
         };
  
       if (!strcmp(t -> tok_name, "~diag_tag_scope"))
         {exp r;
  	diag_info * di = read_diag_tag_scope();
  	r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		   4, 0, diagnose_tag);
  	setfather(r, tkv.tk_exp);
  	dno(r) = di;
  	tkv.tk_exp = r;
  	set_place(old_place);
  	return tkv;
         };
    };
  }

  SET(tkv); /* call looks at done to see if result is meaningful */
  return tkv;
}


