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
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: me_fns.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/10/29  10:10:51  currie
 * 512 bit alignment for hppa
 *
 * Revision 1.3  1995/07/05  09:26:35  currie
 * continue wrong
 *
 * Revision 1.2  1995/05/05  08:10:56  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/




#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "table_fns.h"
#include "externs.h"
#include "installglob.h"
#include "tags.h"
#include "install_fns.h"
#include "check.h"
#include "messages_c.h"
#include "shapemacs.h"
#include "basicread.h"
#include "natmacs.h"
#include "me_fns.h"

  /* a collection of useful procedures for makeing up exps */

/* PROCEDURES */

exp me_obtain
    PROTO_N ( (id) )
    PROTO_T ( exp id )
{
   shape sha = (son(id)==nilexp)?sh(id):sh(son(id));
   exp n;
   n = getexp((isvar(id)) ? f_pointer(align_of(sha)) : sha,
                  nilexp, 0, id, pt(id), 0, 0, name_tag);
   ++no(id);
   pt(id) = n;
   return n;
}

exp me_startid
    PROTO_N ( (sha, def, isv) )
    PROTO_T ( shape sha X exp def X int isv )
{
  exp r = getexp(sha, nilexp, 0, def, nilexp, 0, 0, ident_tag);
  if (isv)
     setvar(r);
  return r;
}

exp me_start_clearvar
    PROTO_N ( (sha, shb) )
    PROTO_T ( shape sha X shape shb )
{
  exp init = getexp(shb, nilexp, 0, nilexp, nilexp, 0, 0, clear_tag);
  exp var = getexp(sha, nilexp, 0, init, nilexp, 0, 0, ident_tag);
  setvar(var);
  return var;
}

exp me_complete_id
    PROTO_N ( (id, body) )
    PROTO_T ( exp id X exp body )
{
  clearlast(son(id));
  bro(son(id)) = body;
  setlast(body);
  bro(body) = id;
  sh(id) = sh(body);
  return hold_check(id);
}

exp me_u1
    PROTO_N ( (ov_err, arg1, nm) )
    PROTO_T ( error_treatment ov_err X exp arg1 X unsigned char nm )
{
  exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp,
           0, 0, nm);
  seterrhandle(r, ov_err.err_code);
  if (isov(r))
    setjmp_dest(r, get_lab(ov_err.jmp_dest));
  setfather (r, arg1);
  return r;
}

exp me_u2
    PROTO_N ( (arg1, nm) )
    PROTO_T ( exp arg1 X unsigned char nm )
{
  exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp, 0, 0, nm);
  setfather (r, arg1);
  return r;
}

exp me_u3
    PROTO_N ( (sha, arg1, nm) )
    PROTO_T ( shape sha X exp arg1 X unsigned char nm )
{
  exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
  setfather (r, arg1);
  return r;
}

exp me_b1
    PROTO_N ( (ov_err, arg1, arg2, nm) )
    PROTO_T ( error_treatment ov_err X exp arg1 X exp arg2 X unsigned char nm )
{
  exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp,
                  0, 0, nm);
  seterrhandle(r, ov_err.err_code);
  setbro(arg1, arg2);
  clearlast(arg1);
  if (isov(r))
    setjmp_dest(r, get_lab(ov_err.jmp_dest));
  setfather (r, arg2);
  return r;
}

exp me_b2
    PROTO_N ( (arg1, arg2, nm) )
    PROTO_T ( exp arg1 X exp arg2 X unsigned char nm )
{
  exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp, 0, 0, nm);
  setbro(arg1, arg2);
  clearlast(arg1);
  setfather (r, arg2);
  return r;
}

exp me_b3
    PROTO_N ( (sha, arg1, arg2, nm) )
    PROTO_T ( shape sha X exp arg1 X exp arg2 X unsigned char nm )
{
  exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
  setbro(arg1, arg2);
  clearlast(arg1);
  setfather (r, arg2);
  return r;
}

exp me_c1
    PROTO_N ( (sha, ov_err, arg1, nm) )
    PROTO_T ( shape sha X error_treatment ov_err X exp arg1 X unsigned char nm )
{
  exp r = getexp (sha, nilexp, 0, arg1, nilexp,
           0, 0, nm);
  seterrhandle(r, ov_err.err_code);
  if (isov(r))
     setjmp_dest(r, get_lab(ov_err.jmp_dest));
  setfather (r, arg1);
  return r;
}

exp me_c2
    PROTO_N ( (sha, arg1, nm) )
    PROTO_T ( shape sha X exp arg1 X unsigned char nm )
{
  exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
  setfather (r, arg1);
  return r;
}

exp me_l1
    PROTO_N ( (s, nm) )
    PROTO_T ( shape s X unsigned char nm )
{
  exp r = getexp (s, nilexp, 0, nilexp, nilexp, 0, 0, nm);
  return r;
}



exp me_q1_aux
    PROTO_N ( (prob, nt, lab, arg1, arg2, nm) )
    PROTO_T ( nat_option prob X ntest nt X exp lab X exp arg1 X exp arg2 X unsigned char nm )
{
  exp r;
  r = getexp (f_top, nilexp, 0, arg1, lab, 0, 0, nm);
  no(r) = (prob.present) ? natint(prob.val) : 1000;
  settest_number(r, nt);
  setbro(arg1, arg2);
  clearlast(arg1);
  ++no(son(lab));
  setfather (r, arg2);
  return r;
}

exp me_q1
    PROTO_N ( (prob, nt, dest, arg1, arg2, nm) )
    PROTO_T ( nat_option prob X ntest nt X label dest X exp arg1 X exp arg2 X unsigned char nm )
{
  return me_q1_aux(prob, nt, get_lab(dest), arg1, arg2, nm);
}

exp me_q2_aux
    PROTO_N ( (prob, err, nt, lab, arg1, arg2, nm) )
    PROTO_T ( nat_option prob X error_treatment err X ntest nt X exp lab X exp arg1 X exp arg2 X unsigned char nm )
{
  exp r;
  UNUSED(err);
  r = getexp (f_top, nilexp, 0, arg1, lab, 0, 0, nm);
  no(r) = (prob.present) ? natint(prob.val) : 1000;
  settest_number(r, nt);
  setbro(arg1, arg2);
  clearlast(arg1);
  ++no(son(lab));
  setfather (r, arg2);

  return r;
}

exp me_q2
    PROTO_N ( (prob, err, nt, dest, arg1, arg2, nm) )
    PROTO_T ( nat_option prob X error_treatment err X ntest nt X label dest X exp arg1 X exp arg2 X unsigned char nm )
{
  return me_q2_aux(prob, err, nt, get_lab(dest), arg1, arg2, nm);
}

exp me_shint
    PROTO_N ( (sha, i) )
    PROTO_T ( shape sha X int i )
{
  return getexp(sha, nilexp, 0, nilexp, nilexp, 0, i, val_tag);
}

exp me_null
    PROTO_N ( (sha, i, nm) )
    PROTO_T ( shape sha X int i X unsigned char nm )
{
  return getexp(sha, nilexp, 0, nilexp, nilexp, 0, i, nm);
}

exp me_b4
    PROTO_N ( (div0_err, ov_err, arg1, arg2, nm) )
    PROTO_T ( error_treatment div0_err X error_treatment ov_err X exp arg1 X exp arg2 X unsigned char nm )
{
  exp id, tst, divexp, seq;

  if (div0_err.err_code != 4)
    return me_b1(ov_err, arg1, arg2, nm);

  id = me_startid(sh(arg1), arg2, 0);
  divexp = me_b1(ov_err, arg1, me_obtain(id), nm);
  tst = me_q1(no_nat_option, f_not_equal, div0_err.jmp_dest,
		 me_obtain(id), me_shint(sh(arg1), 0), test_tag);
  seq = me_b2(me_u2(tst, 0), divexp, seq_tag);
  return me_complete_id(id, seq);
}

void note_repeat
    PROTO_N ( (r) )
    PROTO_T ( exp r )
{
  if (crt_repeat != nilexp)
	  ++no (crt_repeat);
  repeat_list = getexp (f_top, crt_repeat, 0, nilexp,
	    repeat_list, 1, 0, 0);
  crt_repeat = repeat_list;

  pt(r) = crt_repeat;

  son (crt_repeat) = r;
  crt_repeat = bro(crt_repeat);
  return;
}

  /* the result is an alignment for something of which the
     addresses must be divisible by n bits */
alignment long_to_al
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  switch (n) {
    case 0:
    case 1: return const_al1;
    case 8: return const_al8;
    case 16: return const_al16;
    case 32: return const_al32;
    case 64: return const_al64;
    case 512: return const_al512;
    default: failer(BAD_LONG_AL);
             return const_al32;
  };
}

  /* the shape describes an integer */
int is_integer
    PROTO_N ( (s) )
    PROTO_T ( shape s )
{
  return name(s) >= scharhd && name(s) <= u64hd;
}

  /* the shape describes a floating point number */
int is_float
    PROTO_N ( (s) )
    PROTO_T ( shape s )
{
  return name(s) >= shrealhd && name(s) <= doublehd;
}

int is_complex
    PROTO_N ( (s) )
    PROTO_T ( shape s )
{
#if substitute_complex
  return (name(s) == cpdhd);
#else
  return name(s) >= shcomplexhd && name(s) <= complexdoublehd;
#endif
}

floating_variety float_to_complex_var
    PROTO_N ( (f) )
    PROTO_T ( floating_variety f )
{
  return f+3;
}

floating_variety complex_to_float_var
    PROTO_N ( (f) )
    PROTO_T ( floating_variety f )
{
  return f-3;
}
