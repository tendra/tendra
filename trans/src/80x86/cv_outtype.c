/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: cv_outtype.c 740 2005-09-07 07:36:12Z asmodai $
 */
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


/* sco/cv_outtype.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: cv_outtype.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.10  1997/03/24  12:43:40  pwe
 * outn int->long
 *
 * Revision 1.9  1996/02/22  10:03:44  pwe
 * sco diag recursive struct (& clearinlined)
 *
 * Revision 1.8  1995/11/30  10:19:54  pwe
 * diag struct struct
 *
 * Revision 1.7  1995/10/23  17:34:37  pwe
 * dynamic initialisation PIC, and sco diags
 *
 * Revision 1.6  1995/10/18  11:24:43  pwe
 * diag struct
 *
 * Revision 1.5  1995/09/19  15:43:09  pwe
 * round, fp overflow etc
 *
 * Revision 1.4  1995/03/20  09:23:49  pwe
 * move codeview into sco directory
 *
 * Revision 1.3  1995/01/31  13:43:07  pwe
 * correct CR95_034.-g_on_sco:_array_size_1_too_short
 *
 * Revision 1.2  1995/01/30  12:57:05  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/07/13  08:32:41  jmf
 * Initial revision
 *
**********************************************************************/



#include "config.h"
#include "common_types.h"
#include "cv_types.h"
#include "expmacs.h"
#include "out.h"
#include "xalloc.h"


/* PROCEDURES */

ot
out_type(diag_type t, int in_struct)
{
  ot res;

  switch (t -> key)
   {
     case DIAG_TYPE_VARIETY:
       {
         variety v = t->data.var;
         res.modifier = 0;
         res.size = shape_size(v) /8;
         res.type = 04;
         if (res.size == 1) {
           res.type = 02;
	 }
         if (res.size == 2) {
           res.type = 03;
	 }
         if (!is_signed(v)) {
           res.type += 012;
	 }
         break;
       }
     case DIAG_TYPE_FLOAT:
       {
         floating_variety v = t->data.f_var;
         res.modifier = 0;
         res.size = 8;
         res.type = 07;
         if (v == 0) {
            res.type = 06;
            res.size = 4;
	 }
         break;
       }
     case DIAG_TYPE_ARRAY:
       {
         ot arg;
         int lwb = no(t->data.array.lower_b);
         int upb = no(t->data.array.upper_b);
         int n = upb -lwb +1;
         arg = out_type(t->data.array.element_type, in_struct);
         res.modifier = (arg.modifier << 2) + 3;
         res.type = arg.type;
         res.size = arg.size * n;
         outs(".dim ");
         outn((long)n);
         outs("; .size ");
         outn((long)res.size);
         outs("; ");
         break;
       }
     case DIAG_TYPE_PTR:
       {
         ot arg;
         arg = out_type(t->data.ptr.object, in_struct);
         res.modifier = (arg.modifier << 2) + 1;
         res.size = 4;
         res.type = arg.type;
         break;
       }
     case DIAG_TYPE_PROC:
       {
         ot arg;
         arg = out_type(t->data.proc.result_type, in_struct);
         res.modifier = (arg.modifier << 4) + 9;
         res.size = 4;
         res.type = arg.type;
         break;
       }
     case DIAG_TYPE_STRUCT:
       {
         res.modifier = 0;
         res.type = 010;
         res.size = shape_size(t->data.t_struct.tdf_shape) / 8;
         if (t->been_outed == 1) {
           outs(".tag ");
           outs(t->data.t_struct.nme.ints.chars);
           outs("; ");
           outs(".size ");
           outn((long)res.size);
           outs("; ");
         }
         break;
       }
     case DIAG_TYPE_UNION:
       {
         res.modifier = 0;
         res.type = 011;
         res.size = shape_size(t->data.t_union.tdf_shape) / 8;
         if (t->been_outed == 1) {
           outs(".tag ");
           outs(t->data.t_union.nme.ints.chars);
           outs("; ");
           outs(".size ");
           outn((long)res.size);
           outs("; ");
         }
         break;
       }
     case DIAG_TYPE_ENUM:
       {
         ot arg;
         arg = out_type(t->data.t_enum.base_type, in_struct);
         res.modifier = 0;
         res.type = 012;
         res.size = arg.size;
         if (!in_struct) {
           outs(".tag ");
           outs(t->data.t_struct.nme.ints.chars);
           outs("; ");
         }
         outs(".size ");
         outn((long)res.size);
         outs("; ");
         break;
       }
     case DIAG_TYPE_NULL:
       {
         res.modifier = 0;
         res.size = 4;
         res.type = 4;
         break;
       }
     case DIAG_TYPE_LOC:
       res = out_type(t->data.loc.object, in_struct);
       break;
     default:
/*
       failer("outtype not yet implemented");
*/
       res.modifier = 0;
       res.size = 4;
       res.type = 4;
       break;
   }
  return res;
}

static int fixup_no = 0;


static void
fixup(char **n)
{
  if (*n == (char *)0 || (*n)[0] == 0) {
      char * k = (char*)xcalloc(10, sizeof(char));
      k[0] = '.';
      sprintf(&k[1], "%d", fixup_no++);
      strcpy(k + strlen(k), "fake");
      *n = k;
  }
  return;
}

void
out_tagged(diag_type d)
{
  int i;
  if (d->been_outed) {
     return;
  }
  switch (d->key)
   {
     case DIAG_TYPE_STRUCT:
      {
        struct diag_field_list_t fs;
        int sz_in_bits = shape_size(d->data.t_struct.tdf_shape);
        int sz = sz_in_bits / 8;
        fs = *d->data.t_struct.fields;
        fixup(&d->data.t_struct.nme.ints.chars);

	d->been_outed = -1;
        for (i = fs.len - 1; i >= 0; --i) {
	   struct diag_field_t f;
           f = *fs.array[i];
	   out_tagged(f.field_type);
	}

        fprintf(fpout, " .def %s; .scl 10; .type 010; .size %d; .endef\n",
		d->data.t_struct.nme.ints.chars, sz);
	d->been_outed = 1;
        for (i=fs.len-1; i>=0; --i) {
	   struct diag_field_t f;
           ot ty;
           f = *fs.array[i];

           if (f.field_type->key == DIAG_TYPE_BITFIELD) {
             fprintf(fpout,
		     " .def %s; .val %d; .scl 18; .type 04; .size %d; .endef\n",
		     f.field_name.ints.chars, no(f.where),
		     f.field_type->data.bitfield.no_of_bits.nat_val.small_nat);
           } else {
             fprintf(fpout, " .def %s; .val %d; .scl 8; ",
		     f.field_name.ints.chars, no(f.where) / 8);
             ty = out_type(f.field_type, 1);
             fprintf(fpout, ".type 0%o; .endef\n", ty.type +
		     (ty.modifier << 4));
	   }
	}
        fprintf(fpout,
		" .def .eos; .val %d; .scl 102; .tag %s; .size %d; .endef\n",
		sz, d->data.t_struct.nme.ints.chars, sz);
        return;
      }
     case DIAG_TYPE_UNION:
      {
        struct diag_field_list_t fs;
        int sz_in_bits = shape_size(d->data.t_union.tdf_shape);
        int sz = sz_in_bits / 8;
        fs = *d->data.t_union.fields;
        fixup(&d->data.t_union.nme.ints.chars);

	d->been_outed = -1;
        for (i = fs.len - 1; i >= 0; --i) {
	   struct diag_field_t f;
           f = *fs.array[i];
	   out_tagged(f.field_type);
	}

        fprintf(fpout, " .def %s; .scl 12; .type 011; .size %d; .endef\n",
		d->data.t_union.nme.ints.chars, sz);
	d->been_outed = 1;
        for (i = fs.len - 1; i >= 0; --i) {
	   struct diag_field_t f;
           ot ty;
           f = *fs.array[i];

           fprintf(fpout, " .def %s; .val 0; .scl 11; ",
		   f.field_name.ints.chars);
           ty = out_type(f.field_type, 1);
           fprintf(fpout, ".type 0%o; .endef\n", ty.type + (ty.modifier << 4));
	}
        fprintf(fpout,
		" .def .eos; .val %d; .scl 102; .tag %s; .size %d; .endef\n",
		sz, d->data.t_union.nme.ints.chars, sz);
        return;
      }
     case DIAG_TYPE_ENUM:
      {
        struct enum_values_list_t es;
        int sz = 4;
        es = *d->data.t_enum.values;
        fixup(&d->data.t_enum.nme.ints.chars);

        fprintf(fpout, " .def %s; .scl 15; .type 012; .size %d; .endef\n",
		d->data.t_enum.nme.ints.chars, sz);
        for (i = es.len - 1; i >= 0; --i) {
	   struct enum_values_t e;
           e = *es.array[i];
           fprintf(fpout, " .def %s; .val %d; .scl 16; .type 013; .endef\n",
		   e.nme.ints.chars, no(e.val));
	}
        fprintf(fpout,
		" .def .eos; .val %d; .scl 102; .tag %s; .size %d; .endef\n",
		sz, d->data.t_enum.nme.ints.chars, sz);
        return;
      }
     default:
        return;
   }
}
