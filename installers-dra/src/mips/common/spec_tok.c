/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>

#include "config.h"

#include <reader/codetypes.h>
#include <reader/basicread.h>
#include <reader/c_arith_type.h>
#include <reader/natmacs.h>
#include <reader/spec_tok.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>
#include <reader/externs.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/flags.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <diag/diag_fns.h>

#include <refactor/refactor.h>

#include "expmacs.h"

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
