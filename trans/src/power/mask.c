/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include "mask.h"

int right_of_mask(unsigned int m)
{
  int r;
  unsigned int mask = 1;
  for (r = 0;r<=31;r++)
  {
    if ((m & mask)!=0)
    {
      return r;
    }
    mask = mask<<1;
  }
  return 0;
}

int left_of_mask(unsigned int m)
{
  int r;
  unsigned int mask =0x80000000;
  for (r = 31;r>=0;r--)
  {
    if ((m & mask)!=0)
    {
      return r;
    }
    mask = mask>>1;
  }
  return 0;
}

bool
is_a_mask(unsigned int m)
{
  unsigned int j,k;
  /* If m is a mask then true is returned */
  /* The definition of a mask is an unbroken series of 1's */
  if(m==0)
  {
    return false;
  }
  j=( (m-1) ^ m )>>1 ;
  k=j+m;
  return (k&(k+1))==0;
}
