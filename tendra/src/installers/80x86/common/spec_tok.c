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


/* 80x86/spec_tok.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: spec_tok.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1997/10/10  18:25:29  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.8  1997/08/23  13:45:42  pwe
 * initial ANDF-DE
 *
 * Revision 1.7  1997/03/20  16:24:07  pwe
 * dwarf2
 *
 * Revision 1.6  1997/02/18  11:43:08  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.5  1996/12/13  14:39:33  pwe
 * prep NEWDIAGS
 *
 * Revision 1.4  1996/12/10  15:11:52  pwe
 * prep NEWDIAGS
 *
 * Revision 1.3  1996/10/29  14:04:49  pwe
 * remove inbuilt C promote etc, for inclusion of long long
 *
 * Revision 1.2  1995/01/30  12:56:52  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:41:50  jmf
 * Initial revision
 *
**********************************************************************/


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
#include "dg_fns.h"


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

  if (!strcmp(t -> tok_name, "JMFprofile"))  {
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
  if (!strcmp(t -> tok_name, "JMFinline"))  {
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


      s = hold_check(s);

      set_place(old_place);
      tkv.tk_exp = s;
      *done = 1;
      return tkv;
  };
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
  if (!strcmp(t -> tok_name, "~rem"))  {
      exp arg1, arg2;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_check(d_exp());
      arg2 = hold_check(d_exp());

      set_place(old_place);
      tkv.tk_exp = me_b2(arg1, arg2, rem0_tag);
      *done = 1;
      return tkv;
  };
#ifdef INBUILT_PROMOTE
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
      !strcmp(t -> tok_name, "~diag_tag_scope")
#ifdef NEWDIAGS
	|| !strcmp(t -> tok_name, "~dg_exp")
#endif
     )  {

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
       {
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

     if (!strcmp(t -> tok_name, "~diag_id_scope"))
       {
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

     if (!strcmp(t -> tok_name, "~diag_type_scope"))
       {
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

     if (!strcmp(t -> tok_name, "~diag_tag_scope"))
       {
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
     if (!strcmp(t -> tok_name, "~dg_exp"))
       {
        tkv.tk_exp = read_dg_exp (tkv.tk_exp);
        set_place(old_place);
        return tkv;
       };
#endif

  };

  if (!strncmp(t -> tok_name, "~asm", 4)) {
    int prp;
    exp arg1;
    place old_place;
    old_place = keep_place();
    if (!strcmp(t -> tok_name, "~asm")) {
      set_place(pars);
      arg1 = hold_check (f_make_nof_int (ucharsh, d_string()));
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
      arg1 = hold_check (d_exp());
    }
    set_place(old_place);
    tkv.tk_exp = getexp (f_top, nilexp, 0, arg1, nilexp, prp, 0, asm_tag);
    setfather (tkv.tk_exp, arg1);
    *done = 1;
    return tkv;
  }

  SET(tkv); /* call looks at done to see if result is meaningful */
  return tkv;
}
