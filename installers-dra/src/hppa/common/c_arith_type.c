/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/arith_codes.h>

#include <construct/install_fns.h>

/* PROCEDURES */

int
arith_type(int a, int b)
{
 if(a==(t_long|t_unsigned))return a;
 if(b==(t_long|t_unsigned))return a;
 if(a==(t_long|t_signed)){
   if(b==(t_int|t_unsigned))return t_long|t_unsigned;
   return a;
   }
 if(b==(t_long|t_signed)){
   if(a==(t_int|t_unsigned))return t_long|t_unsigned;
   return b;
   }
 if(a==(t_int|t_unsigned))return a;
 if(b==(t_int|t_unsigned))return b;
 return t_int|t_signed;
}

int
promote(int a)
{
 if((a&variety_filter)<t_int)return t_int|t_signed;
 return a;
}

int
sign_promote(int a)
{
 if((a&variety_filter)<t_int)a=((a&~variety_filter)|t_int);
 return a;
}

variety
convert(unsigned a)
{
 switch(a){
   case (t_char|t_none): return scharsh;
   case (t_char|t_signed): return scharsh;
   case (t_char|t_unsigned): return ucharsh;
   case (t_short|t_signed): return swordsh;
   case (t_short|t_unsigned): return uwordsh;

   case (t_int|t_signed): return slongsh;
   case (t_int|t_unsigned): return ulongsh;
   case (t_long|t_signed): return slongsh;
   case (t_long|t_unsigned): default: return ulongsh;
   }
 }
