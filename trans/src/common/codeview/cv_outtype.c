/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/xalloc.h>

#include <reader/exp.h>

#include <construct/installtypes.h>

#ifndef TDF_DIAG4
#include <diag3/dg_first.h>
#include <diag3/dg_types.h>  /* TDF_DIAG4 */
#include <diag3/diagtypes.h> /* TDF_DIAG3 */
#endif

#include <main/driver.h>
#include <main/print.h>

#include "cv_types.h"
#include "cv_outtype.h"

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
         asm_printf(".dim %d; .size %d; ", n, res.size);
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
           asm_printf(".tag %s; .size %d; ", t->data.t_struct.nme.ints.chars, res.size);
         }
         break;
       }
     case DIAG_TYPE_UNION:
       {
         res.modifier = 0;
         res.type = 011;
         res.size = shape_size(t->data.t_union.tdf_shape) / 8;
         if (t->been_outed == 1) {
           asm_printf(".tag %s; .size %d; ", t->data.t_union.nme.ints.chars, res.size);
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
           asm_printf(".tag %s; ", t->data.t_struct.nme.ints.chars);
         }
         asm_printf(".size %d; ", res.size);
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

        asm_printf( " .def %s; .scl 10; .type 010; .size %d; .endef\n",
		d->data.t_struct.nme.ints.chars, sz);
	d->been_outed = 1;
        for (i=fs.len-1; i>=0; --i) {
	   struct diag_field_t f;
           ot ty;
           f = *fs.array[i];

           if (f.field_type->key == DIAG_TYPE_BITFIELD) {
             asm_printf(
		     " .def %s; .val %d; .scl 18; .type 04; .size %d; .endef\n",
		     f.field_name.ints.chars, no(f.where),
		     f.field_type->data.bitfield.no_of_bits.nat_val.small_nat);
           } else {
             asm_printf( " .def %s; .val %d; .scl 8; ",
		     f.field_name.ints.chars, no(f.where) / 8);
             ty = out_type(f.field_type, 1);
             asm_printf( ".type 0%o; .endef\n", ty.type +
		     (ty.modifier << 4));
	   }
	}
        asm_printf(
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

        asm_printf( " .def %s; .scl 12; .type 011; .size %d; .endef\n",
		d->data.t_union.nme.ints.chars, sz);
	d->been_outed = 1;
        for (i = fs.len - 1; i >= 0; --i) {
	   struct diag_field_t f;
           ot ty;
           f = *fs.array[i];

           asm_printf( " .def %s; .val 0; .scl 11; ",
		   f.field_name.ints.chars);
           ty = out_type(f.field_type, 1);
           asm_printf( ".type 0%o; .endef\n", ty.type + (ty.modifier << 4));
	}
        asm_printf(
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

        asm_printf( " .def %s; .scl 15; .type 012; .size %d; .endef\n",
		d->data.t_enum.nme.ints.chars, sz);
        for (i = es.len - 1; i >= 0; --i) {
	   struct enum_values_t e;
           e = *es.array[i];
           asm_printf( " .def %s; .val %d; .scl 16; .type 013; .endef\n",
		   e.nme.ints.chars, no(e.val));
	}
        asm_printf(
		" .def .eos; .val %d; .scl 102; .tag %s; .size %d; .endef\n",
		sz, d->data.t_enum.nme.ints.chars, sz);
        return;
      }
     default:
        return;
   }
}
