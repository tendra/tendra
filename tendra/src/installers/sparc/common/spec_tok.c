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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/spec_tok.c,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: spec_tok.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.17  1997/10/10  18:33:06  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.16  1997/08/23  13:54:40  pwe
 * initial ANDF-DE
 *
 * Revision 1.15  1997/04/04  15:23:10  pwe
 * tidy re old DWARF interface
 *
 * Revision 1.14  1997/02/18  11:48:30  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.13  1996/09/06  17:18:15  pwe
 * explicit next_callee_offset to correct double alignment
 *
 * Revision 1.12  1996/08/27  14:09:15  pwe
 * ensure all varargs are stored, and ptr is not64bit
 *
 * Revision 1.11  1996/08/23  12:07:57  pwe
 * treat complex parameter as struct
 *
 * Revision 1.10  1996/08/20  12:21:30  pwe
 * structures (etc) in varargs
 *
 * Revision 1.9  1996/08/15  16:27:03  pwe
 * add missing file headers
 *
 * Revision 1.8  1995/10/18  14:09:02  john
 * Fix to ANSI va_start
 *
 * Revision 1.7  1995/09/20  12:30:55  john
 * Portability fix
 *
 * Revision 1.6  1995/09/15  16:18:10  john
 * New token
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
--------------------------------------------------------------------------
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
#include "translat.h"
#include "spec_tok.h"
#include "new_tags.h"
#include "myassert.h"
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

  /* Added for VARARGS on sparc etc */

  if (!strcmp(t -> tok_name,"ansi.stdarg.__va_start") ) {
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

    env_o = getexp(f_offset(f_callers_alignment(1), f_alignment(sh(arg1))),
		   nilexp, 0, id, nilexp, 0, 0, env_offset_tag);
    setvis(id);
    setenvoff(id);

    tkv.tk_exp = hold_check(f_add_to_ptr(f_current_env(), env_o));
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
    arg1 = hold_check(d_exp());
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

    tkv.tk_exp = hold_check (me_complete_id (id, f_sequence (el, con)));
    *done = 1;
    return tkv;
  }
  /* end of addition for VARARGS */

  if (!strcmp(t -> tok_name,"~next_caller_offset") ) {
    exp arg1;
    shape s1, s2;
    place old_place;
    old_place = keep_place();
    set_place(pars);
    arg1 = hold_check(d_exp());
    s1 = d_shape();
    s2 = d_shape();
    set_place(old_place);
    caller_offset_used = 1;

    if (sparccpd(s1)) {
      s1 = f_pointer (f_alignment (s1));
    }

    tkv.tk_exp = hold_check (f_offset_pad (f_parameter_alignment (s2),
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
    arg1 = hold_check(d_exp());
    s1 = d_shape();
    s2 = d_shape();
    set_place(old_place);

    tkv.tk_exp = hold_check (f_offset_pad (f_parameter_alignment (s2),
				f_offset_pad (f_alignment (s2),
				   f_offset_add (arg1, f_shape_offset (s1)))));
    *done = 1;
    return tkv;
  }


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

 if(!strcmp(t->tok_name, "~Sync_handler")){
    tkv.tk_exp = getexp(f_top,nilexp,0,nilexp,nilexp,0,0,special_tag);
    *done = 1;
    return tkv;
  }

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
      failer("Unsupported argument to token __alpha_special");
      tkv.tk_exp = getexp(f_top,nilexp,0,nilexp,nilexp,0,0,null_tag);
      *done = 1;
    }
    set_place(old_place);
    return tkv;
  }
  


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

    if (!diagnose){
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
