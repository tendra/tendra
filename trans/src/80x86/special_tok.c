/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>

#include <reader/expmacs.h>

#include <reader/codetypes.h>
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>
#include <reader/c_arith_type.h>
#include <reader/natmacs.h>
#include <reader/special_tok.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include <refactor/refactor.h>

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#include <newdiag/dg_fns.h>
#else
#include <diag/diag_fns.h>
#include <diag/dg_fns.h>
#endif

/* intercepts specially defined tokens */

tokval special_token
(token t, bitstream pars, int sortcode, int * done)
{
  tokval tkv;
  UNUSED(sortcode);

  if (t -> tok_name == (char*)0) {
    SET(tkv); /* call looks at done to see if result is meaningful */
    return tkv;
  };

  if (builtin & BUILTIN_DEBUG) {
    if (!strcmp(t -> tok_name, "JMFprofile")) {
        nat n;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        n = d_nat();
    
        set_place(old_place);
        tkv.tk_exp = f_profile(n);
        *done = 1;
        return tkv;
    };
    if (!strcmp(t -> tok_name, "JMFinline")) {
        exp s;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        IGNORE d_shape();
        s = d_exp();
        if (name(s) == apply_tag)
    	settoinline(s);
        if (name(s) == ident_tag && name(son(s)) == clear_tag &&
    		name(bro(son(s))) == seq_tag &&
    		name(son(son(bro(son(s))))) == apply_tag)
    	settoinline(son(son(bro(son(s)))));
    
    
        s = hold_refactor(s);
    
        set_place(old_place);
        tkv.tk_exp = s;
        *done = 1;
        return tkv;
    };
  }

  if (builtin & BUILTIN_DIV) {
    if (!strcmp(t -> tok_name, "~div")) {
        exp arg1, arg2;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        arg1 = hold_refactor(d_exp());
        arg2 = hold_refactor(d_exp());
  
        set_place(old_place);
        tkv.tk_exp = me_b2(arg1, arg2, div0_tag);
        *done = 1;
        return tkv;
    };
    if (!strcmp(t -> tok_name, "~rem")) {
        exp arg1, arg2;
        place old_place;
        old_place = keep_place();
        set_place(pars);
        arg1 = hold_refactor(d_exp());
        arg2 = hold_refactor(d_exp());
  
        set_place(old_place);
        tkv.tk_exp = me_b2(arg1, arg2, rem0_tag);
        *done = 1;
        return tkv;
    };
  }

  if (builtin & BUILTIN_PROMOTE) {
    if (!strcmp(t -> tok_name, "~arith_type")) {
      int a, b;
      place old_place;
      signed_nat sn;
      old_place = keep_place();
      set_place(pars);
      sn = d_signed_nat();
      a = snatint(sn);
      sn = d_signed_nat();
      b = snatint(sn);
      set_place(old_place);
      snatint(sn) = arith_type(a, b);
      tkv.tk_signed_nat = sn;
      *done = 1;
      return tkv;
    };
    if (!strcmp(t -> tok_name, "~promote")) {
      int a;
      place old_place;
      signed_nat sn;
      old_place = keep_place();
      set_place(pars);
      sn = d_signed_nat();
      a = snatint(sn);
      set_place(old_place);
      snatint(sn) = promote(a);
      tkv.tk_signed_nat = sn;
      *done = 1;
      return tkv;
    };
    if (!strcmp(t -> tok_name, "~sign_promote")) {
      int a;
      place old_place;
      signed_nat sn;
      old_place = keep_place();
      set_place(pars);
      sn = d_signed_nat();
      a = snatint(sn);
      set_place(old_place);
      snatint(sn) = sign_promote(a);
      tkv.tk_signed_nat = sn;
      *done = 1;
      return tkv;
    };
    if (!strcmp(t -> tok_name, "~convert")) {
      int a;
      place old_place;
      signed_nat sn;
      old_place = keep_place();
      set_place(pars);
      sn = d_signed_nat();
      a = snatint(sn);
      set_place(old_place);
      tkv.tk_variety = convert((unsigned)a);
      *done = 1;
      return tkv;
    };
  }

  if (builtin & BUILTIN_ALLOCA) {
    if (!strcmp(t -> tok_name, "~alloca")) {
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
        !strcmp(t -> tok_name, "~diag_tag_scope")
#ifdef NEWDIAGS
  	|| !strcmp(t -> tok_name, "~dg_exp")
#endif
      ) {

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
         {
#ifdef NEWDIAGS
  	tkv.tk_exp = read_exp_to_source(tkv.tk_exp);
#else
          diag_info * di = read_exp_to_source();
          exp r = getexp(sh(tkv.tk_exp), NULL, 0, tkv.tk_exp, NULL,
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

       if (!strcmp(t -> tok_name, "~diag_id_scope"))
         {
#ifdef NEWDIAGS
          tkv.tk_exp = read_diag_id_scope(tkv.tk_exp);
#else
          diag_info * di = read_diag_id_scope();
          exp r = getexp(sh(tkv.tk_exp), NULL, 0, tkv.tk_exp, NULL,
                     2, 0, diagnose_tag);
          setfather(r, tkv.tk_exp);
          dno(r) = di;
          tkv.tk_exp = r;
#endif
          set_place(old_place);
          return tkv;
         };

       if (!strcmp(t -> tok_name, "~diag_type_scope"))
         {
#ifdef NEWDIAGS
          tkv.tk_exp = read_diag_type_scope(tkv.tk_exp);
#else
          diag_info * di = read_diag_type_scope();
          exp r = getexp(sh(tkv.tk_exp), NULL, 0, tkv.tk_exp, NULL,
                     3, 0, diagnose_tag);
          setfather(r, tkv.tk_exp);
          dno(r) = di;
          tkv.tk_exp = r;
#endif
          set_place(old_place);
          return tkv;
         };

       if (!strcmp(t -> tok_name, "~diag_tag_scope"))
         {
#ifndef NEWDIAGS
          diag_info * di = read_diag_tag_scope();
          exp r = getexp(sh(tkv.tk_exp), NULL, 0, tkv.tk_exp, NULL,
                     4, 0, diagnose_tag);
          setfather(r, tkv.tk_exp);
          dno(r) = di;
          tkv.tk_exp = r;
#endif
          set_place(old_place);
          return tkv;
         };

#ifdef NEWDIAGS
       if (!strcmp(t -> tok_name, "~dg_exp"))
         {
          tkv.tk_exp = read_dg_exp(tkv.tk_exp);
          set_place(old_place);
          return tkv;
         };
#endif
    };
  }

  if (builtin & BUILTIN_ASM) {
    if (!strncmp(t -> tok_name, "~asm", 4)) {
      int prp;
      exp arg1;
      place old_place;
      old_place = keep_place();
      if (!strcmp(t -> tok_name, "~asm")) {
        set_place(pars);
        arg1 = hold_refactor(f_make_nof_int(ucharsh, d_string()));
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
      tkv.tk_exp = getexp(f_top, NULL, 0, arg1, NULL, prp, 0, asm_tag);
      setfather(tkv.tk_exp, arg1);
      *done = 1;
      return tkv;
    }
  }

  SET(tkv); /* call looks at done to see if result is meaningful */
  return tkv;
}
