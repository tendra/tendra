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


/*
$Log: spec_tok.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/10/24  15:51:21  wfs
 * Added "~alloc_size" special token. Minor change to alloca_tag - only need
 * one word for storage of pointer. Major change to round_tag (rounding to
 * unsigned chars) in the fix of avs bug.
 *
 * Revision 1.5  1996/08/30  09:02:33  wfs
 * Various fixes of bugs arising from avs and pl_tdf tests.
 *
 * Revision 1.4  1996/08/06  10:50:13  wfs
 * bug fixes to pic code, enum diagnostics enabled.
 *
 * Revision 1.3  1996/02/14  17:19:22  wfs
 * "next_caller_offset" and "next_callee_offset" have become special tokens
 * defined in "spec_tok.c". Bug fix to a "and_tag" optimization in
 * "oprators.c". A few bug fixes in "makecode.c" arising from the variable
 * caller tests. "promote_pars" defined in "config.h".
 *
 * Revision 1.2  1995/12/18  13:12:33  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  10:30:56  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:30:56  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:28:10  16:28:10  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:58  11:18:58  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:47  15:28:47  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:18:17  13:18:17  wfs (William Simmonds)
 * Initial revision
 * 
*/


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
#include "shapemacs.h"
#include "spec_tok.h"
#include "szs_als.h"


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


  /* Added for VARARGS */

  if (!strcmp(t -> tok_name,"ansi.stdarg.__va_start")) {
	exp arg1;
	exp id;
	exp env_o;
	place old_place;
	old_place = keep_place();
	set_place(pars);
	arg1 = hold_check(d_exp());
	set_place(old_place);
	if (name(arg1) != name_tag) failer("Not a tag in va_start");
	id = son(arg1);

	env_o = getexp(f_offset(frame_alignment, f_alignment(sh(arg1))),
			nilexp, 0, id, nilexp, 0, 0, env_offset_tag);
	setvis(id);
	setenvoff(id);
	tkv.tk_exp = hold_check(f_add_to_ptr(f_add_to_ptr(f_current_env(), env_o),f_shape_offset(sh(arg1))));
	kill_exp(arg1,arg1);
	*done = 1;
	return tkv;
   }
  /* end of addition for VARARGS */

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

#if ishppa
  if (!strcmp(t -> tok_name,"~next_caller_offset")) {
      exp arg1, arg2;
      shape sha1, sha2, sha3;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_check(d_exp());
      sha1 = d_shape();
      sha2 = d_shape();
      set_place(old_place);
      sha3 = (shape_size(sha2)>64 ? f_pointer(f_alignment(sha2)) :
				    (shape_size(sha2)<32 ? swordsh : sha2));
      arg2 = hold_check(f_offset_pad(f_parameter_alignment(sha3),
				     f_shape_offset(sha3)));
      if ((shape_size(sha1)<=32 || shape_size(sha1)>64) &&                              shape_size(sha3)==64)
      {
	 arg1 = hold_check(f_offset_pad(f_parameter_alignment(realsh),arg1));
      }
      tkv.tk_exp = hold_check(me_b3(f_offset(al1_of(sh(arg1)),
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
      arg1 = hold_check(d_exp());
      sha1 = d_shape();
      sha2 = d_shape();
      set_place(old_place);
      arg2 = hold_check(f_offset_pad(f_parameter_alignment(sha1),
				     f_shape_offset(sha1)));
      off = hold_check(me_b3(f_offset(al1_of(sh(arg1)),
				      al2_of(sh(arg2))),
			     arg1,arg2,offset_add_tag));
      if (shape_align(sha1) < shape_align(sha2))
      {
	 tkv.tk_exp = hold_check(f_offset_pad(f_parameter_alignment(sha2),off));
      }
      else
      {
	 tkv.tk_exp = off;
      }
      *done = 1;
      return tkv;
  }

  if (!strcmp(t -> tok_name,"~alloc_size")) {
      exp off,off1,arg1;
      place old_place;
      old_place = keep_place();
      set_place(pars);
      arg1 = hold_check(d_exp());
      set_place(old_place);
      off1 = hold_check(f_offset_pad(SLONG_ALIGN,arg1));
      off = hold_check(me_b3(f_offset(al1_of(sh(off1)),
				      SLONG_ALIGN),
			     off1,f_shape_offset(slongsh),offset_add_tag));
      tkv.tk_exp = hold_check(f_offset_pad(const_al512,off));
      *done = 1;
      return tkv;
  }

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



