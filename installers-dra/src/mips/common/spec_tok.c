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
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: spec_tok.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/

/*
^^^	21/12/92  jmf	Added ~div as special token
^^^	26/03/93  jmf	Changes for new spec 2.1
^^^	24/05/93  jmf	Added ~alloca as special token, not alloc
^^^	10/06/93  jmf	Change long to int, remove extern declarations.
^^^	19/08/93  jmf	Put arith_type, promote, sign_promote, convert
^^^			into c_arith-type.h in machine directories.
^^^	19/08/93  jmf	Set crt_lno in exp_to_source
^^^	23/09/93  jmf	Use natmacs.h
*/

#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "diag_fns.h"
#include "flags.h"
#include "check.h"
#include "me_fns.h"
#include "externs.h"
#include "installglob.h"
#include "messages_r.h"
#include "main_reads.h"
#include "install_fns.h"
#include "c_arith_type.h"
#include "natmacs.h"
#include "spec_tok.h"


/* intercepts specially defined tokens */

tokval special_token
    PROTO_N ( (t, pars, sortcode, done) )
    PROTO_T ( token t X bitstream pars X int sortcode X int * done )
{
  tokval tkv;
  UNUSED(sortcode);

  if (t -> tok_name == (char*)0) {
    SET(tkv); /* call looks at done to see if result is meaningful */
    return tkv;
  };

#if is80x86
  if (!strcmp(t -> tok_name, "~div"))  {
      exp arg1, arg2;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_check(d_exp());
      arg2 = hold_check(d_exp());

      set_place(old_place);
      tkv.tk_exp = me_b2(arg1, arg2, div0_tag);
      *done = 1;
      return tkv;
  };
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
#endif
  if (!strcmp(t -> tok_name, "~alloca"))  {
      exp arg1;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_check(d_exp());
      set_place(old_place);
      tkv.tk_exp = hold_check(me_u3(f_pointer(long_to_al(8)),
			   arg1, alloca_tag));
      *done = 1;
      has_alloca = 1;
      return tkv;
  };

  if (!strcmp(t -> tok_name, "~exp_to_source") ||
      !strcmp(t -> tok_name, "~diag_id_scope") ||
      !strcmp(t -> tok_name, "~diag_type_scope") ||
      !strcmp(t -> tok_name, "~diag_tag_scope"))  {

      place old_place;
      old_place = keep_place();
      set_place(pars);
      tkv.tk_exp = hold_check(d_exp());
      *done = 1;

      if (!diagnose)
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

  SET(tkv); /* call looks at done to see if result is meaningful */
  return tkv;
}
