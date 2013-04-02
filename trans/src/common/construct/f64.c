/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "expmacs.h"

#include <reader/basicread.h>

#include <construct/flpttypes.h>
#include <construct/messages_c.h>
#include <construct/flpt.h>
#include <construct/exp.h>
#include <construct/f64.h>


/* PROCEDURES */

flt64
flt_to_f64(flpt fp, int sg, int *ov)
{
  flt *f = &flptnos[fp];
  flt64 res;
  int i = f->exp;
  *ov = 0;

  if (f->sign == 0 || i < 0) {
    res.big = 0;
    res.small = 0;
  } else {
    res.big = 0;
    res.small = f->mant[i];
    if (i > 0) {
      res.small += (unsigned int)(f->mant[i - 1] << 16);
    }
    if (i > 1) {
      res.big = (int)f->mant[i - 2];
    }
    if (i > 2) {
      res.big += (int)(f->mant[i - 3] << 16);
    }
    if (i > 3 || (sg && res.big < 0)) {
      *ov = 1;
    }
  }

  if (f->sign == -1) {
    res.small = ~res.small;
    res.big = ~res.big;
    if (res.small == 0xffffffff) {
      ++res.big;
    }
    ++res.small;
  }

  return res;
}


flpt
f64_to_flt(flt64 a, int sg)
{
  flpt r = new_flpt();
  flt *res = &flptnos[r];
  flt_zero(res);

  if (a.big == 0 && a.small == 0) {
    return r;
  }

  if (sg && a.big < 0) {
    a.small = ~a.small;
    a.big = ~a.big;
    if (a.small == 0xffffffff) {
      ++a.big;
    }
    ++a.small;
    res->sign = -1;
  } else {
    res->sign = 1;
  }

  if (a.big == 0) {
    if ((a.small & 0xffff0000) == 0) {
      res->exp = 0;
      res->mant[0] = (unsigned short)(a.small & 0xffff);
    } else {
      res->exp = 1;
      res->mant[0] = (unsigned short)((a.small & 0xffff0000) >> 16);
      res->mant[1] = (unsigned short)(a.small & 0xffff);
    }
  } else {
    if ((a.big & (int)0xffff0000) == 0) {
      res->exp = 2;
      res->mant[0] = (unsigned short)(a.big & 0xffff);
      res->mant[1] = (unsigned short)((a.small & 0xffff0000) >> 16);
      res->mant[2] = (unsigned short)(a.small & 0xffff);
    } else {
      res->exp = 3;
      res->mant[0] = (unsigned short)(((unsigned int)a.big >> 16) & 0xffff);
      res->mant[1] = (unsigned short)(a.big & 0xffff);
      res->mant[2] = (unsigned short)((a.small & 0xffff0000) >> 16);
      res->mant[3] = (unsigned short)(a.small & 0xffff);
    }
  }

  return r;
}


int
f64_to_flpt(flt64 a, int sg, int *pr, int sz)
{
  int t = (int)a.small;
  *pr = 0;

  if (sg && (t >> 31) == a.big) {
    return t;
  }

  if (!sg && a.big == 0 && ((a.small & 0x80000000) == 0 || sz <= 32)) {
    return t;
  }

  *pr = 1;
  return f64_to_flt(a, sg);
}


flt64
int_to_f64(int i, int sg)
{
  flt64 res;
  res.small = (unsigned int)i;
  if (sg && i < 0) {
    res.big = -1;
  } else {
    res.big = 0;
  }
  return res;
}


flt64
exp_to_f64(exp e)
{
  int ov;
  if (isbigval(e)) {
    return flt_to_f64(no(e), is_signed(sh(e)), &ov);
  }
  return int_to_f64(no(e), is_signed(sh(e)));
}
