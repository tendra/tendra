/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>

#include <shared/check.h>

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

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#include <newdiag/dg_fns.h>
#else
#include <diag/diag_fns.h>
#include <diag/dg_fns.h>
#endif

#include <refactor/refactor.h>

#include "expmacs.h"
#include "translat.h"
#include "new_tags.h"
#include "localflags.h"

/* intercepts specially defined tokens */


tokval 
special_token ( token t, bitstream pars, int sortcode, int * done )
{
  tokval tkv;
  UNUSED(sortcode);

  if (t -> tok_name == (char*)0) {
    SET(tkv); /* call looks at done to see if result is meaningful */
    return tkv;
  };

  if (builtin & BUILTIN_VARARG) {
    if (!strcmp(t -> tok_name,"ansi.stdarg.__va_start") ) {
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
  
      env_o = getexp(f_offset(f_callers_alignment(1), f_alignment(sh(arg1))),
  		   nilexp, 0, id, nilexp, 0, 0, env_offset_tag);
      setvis(id);
      setenvoff(id);
  
      tkv.tk_exp = hold_refactor(f_add_to_ptr(f_current_env(), env_o));
      kill_exp(arg1,arg1);
      *done = 1;
      return tkv;
    }
  
    if (!strcmp(t -> tok_name,"ansi.stdarg.va_arg") ) {
      exp arg1;
      shape s, s1;
      exp id, ass, con;
      exp_list el;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_refactor(d_exp());
      s = d_shape();
      set_place(old_place);
  
      s1 = s;
      if (sparccpd(s)) {
        s1 = f_pointer (f_alignment (s));
      }
      id = me_startid (f_pointer(f_var_param_alignment), arg1, 0);
      ass = f_assign (me_obtain(id),
  	    f_add_to_ptr (f_contents (f_pointer(f_var_param_alignment), me_obtain(id)),
  		f_offset_pad (f_var_param_alignment, f_shape_offset (s1))));
      con = f_contents (s1,
  	    f_add_to_ptr (f_contents (f_pointer(f_var_param_alignment), me_obtain(id)),
  		f_offset_negate (f_offset_pad (f_var_param_alignment, f_shape_offset (s1)))));
      if (sparccpd(s)) {
        con = f_contents (s, con);
      }
      el = new_exp_list(1);
      el = add_exp_list(el, ass, 0);
  
      tkv.tk_exp = hold_refactor(me_complete_id (id, f_sequence (el, con)));
      *done = 1;
      return tkv;
    }
  }
 

  /* TODO: BUILTIN_? */ {
    if (!strcmp(t -> tok_name,"~next_caller_offset") ) {
      exp arg1;
      shape s1, s2;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_refactor(d_exp());
      s1 = d_shape();
      s2 = d_shape();
      set_place(old_place);
      caller_offset_used = 1;
  
      if (sparccpd(s1)) {
        s1 = f_pointer (f_alignment (s1));
      }
  
      tkv.tk_exp = hold_refactor(f_offset_pad (f_parameter_alignment (s2),
  				f_offset_add (arg1, f_shape_offset (s1))));
      *done = 1;
      return tkv;
    }
  
    if (!strcmp(t -> tok_name,"~next_callee_offset") ) {
      exp arg1;
      shape s1, s2;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_refactor(d_exp());
      s1 = d_shape();
      s2 = d_shape();
      set_place(old_place);
  
      tkv.tk_exp = hold_refactor(f_offset_pad (f_parameter_alignment (s2),
  				f_offset_pad (f_alignment (s2),
  				   f_offset_add (arg1, f_shape_offset (s1)))));
      *done = 1;
      return tkv;
    }
  }

  if (builtin & BUILTIN_ALLOCA) {
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

  /* TODO: BUILTIN_? */ {
    if (!strcmp(t->tok_name, "~Sync_handler")){
       tkv.tk_exp = getexp(f_top,nilexp,0,nilexp,nilexp,0,0,special_tag);
       *done = 1;
       return tkv;
    }
  }

  /* XXX: is this redundant wrt ~asm* below? */
  if (builtin & BUILTIN_ASM) {
    if (!strcmp(t->tok_name, "__sparc_special")){
      exp arg;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg = d_exp();
      assert(name(arg) == val_tag);
      if(no(arg) == 0){
        tkv.tk_exp = getexp(f_bottom,nilexp,0,nilexp,nilexp,0,0,special_tag);
        *done = 1;
      }
      else{
        failer("Unsupported argument to token __sparc_special");
        tkv.tk_exp = getexp(f_top,nilexp,0,nilexp,nilexp,0,0,null_tag);
        *done = 1;
      }
      set_place(old_place);
      return tkv;
    }
  }
  
  if (builtin & BUILTIN_DIAG) {
    if (!strcmp(t -> tok_name, "~exp_to_source") ||
        !strcmp(t -> tok_name, "~diag_id_scope") ||
        !strcmp(t -> tok_name, "~diag_type_scope") ||
        !strcmp(t -> tok_name, "~diag_tag_scope")
#ifdef NEWDIAGS
  	|| !strcmp(t -> tok_name, "~dg_exp")
#endif
       )  {
  	
      place old_place;
      old_place = keep_place();
      set_place(pars);
      tkv.tk_exp = hold_refactor(d_exp());
      *done = 1;

      if (diag == DIAG_NONE) {
        set_place(old_place);
        return tkv;
      };

      if (!strcmp(t -> tok_name, "~exp_to_source")){
#ifdef NEWDIAGS
        tkv.tk_exp = read_exp_to_source (tkv.tk_exp);
#else
        diag_info * di = read_exp_to_source();
        exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		 1, 0, diagnose_tag);
        setfather(r, tkv.tk_exp);
        dno(r) = di;
        tkv.tk_exp = r;
        crt_lno = natint(di -> data.source.end.line_no);
        crt_charno = natint(di -> data.source.end.char_off);
        crt_flnm = di -> data.source.beg.file->file.ints.chars;
#endif
        set_place(old_place);
        return tkv;
      };

      if (!strcmp(t -> tok_name, "~diag_id_scope")){
#ifdef NEWDIAGS
        tkv.tk_exp = read_diag_id_scope (tkv.tk_exp);
#else
        diag_info * di = read_diag_id_scope();
        exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		 2, 0, diagnose_tag);
        setfather(r, tkv.tk_exp);
        dno(r) = di;
        tkv.tk_exp = r;
#endif
        set_place(old_place);
        return tkv;
      };

      if (!strcmp(t -> tok_name, "~diag_type_scope")){
#ifdef NEWDIAGS
        tkv.tk_exp = read_diag_type_scope (tkv.tk_exp);
#else
        diag_info * di = read_diag_type_scope();
        exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		 3, 0, diagnose_tag);
        setfather(r, tkv.tk_exp);
        dno(r) = di;
        tkv.tk_exp = r;
#endif
        set_place(old_place);
        return tkv;
      };

      if (!strcmp(t -> tok_name, "~diag_tag_scope")){
#ifndef NEWDIAGS
        diag_info * di = read_diag_tag_scope();
        exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
  		 4, 0, diagnose_tag);
        setfather(r, tkv.tk_exp);
        dno(r) = di;
        tkv.tk_exp = r;
#endif
        set_place(old_place);
        return tkv;
      };

#ifdef NEWDIAGS
     if (!strcmp(t -> tok_name, "~dg_exp")){
        tkv.tk_exp = read_dg_exp (tkv.tk_exp);
        set_place(old_place);
        return tkv;
      };
#endif
    }
  }

  if (builtin & BUILTIN_ASM) {
    if (!strncmp(t -> tok_name, "~asm", 4)) {
      int prp;
      exp arg1;
      place old_place;
      old_place = keep_place();
      if (!strcmp(t -> tok_name, "~asm")) {
        set_place(pars);
        arg1 = hold_refactor(f_make_nof_int (ucharsh, d_string()));
        prp = 1;
      }
      else {
        if (!strcmp(t -> tok_name, "~asm_sequence"))
  	prp = 0;
        else
        if (!strcmp(t -> tok_name, "~asm_exp_input"))
  	prp = 2;
        else
        if (!strcmp(t -> tok_name, "~asm_exp_output"))
  	prp = 4;
        else
        if (!strcmp(t -> tok_name, "~asm_exp_address"))
  	prp = 8;
        else
  	return tkv;
        set_place(pars);
        arg1 = hold_refactor(d_exp());
      }
      set_place(old_place);
      tkv.tk_exp = getexp (f_top, nilexp, 0, arg1, nilexp, prp, 0, asm_tag);
      setfather (tkv.tk_exp, arg1);
      *done = 1;
      return tkv;
    }
  }

  SET(tkv); /* call looks at done to see if result is meaningful */
  return tkv;
}
