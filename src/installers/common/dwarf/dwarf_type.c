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
$Date: 1998/02/04 10:43:38 $
$Revision: 1.2 $
$Log: dwarf_type.c,v $
 * Revision 1.2  1998/02/04  10:43:38  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1996/07/05  09:03:58  pwe
 * correction for enums
 *
 * Revision 1.6  1996/03/13  13:50:37  pwe
 * diags for long long
 *
 * Revision 1.5  1995/11/28  13:40:31  pwe
 * int more likely than long for 32 bit
 *
 * Revision 1.4  1995/09/28  12:40:00  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.3  1995/09/13  16:13:18  pwe
 * tidy for gcc
 *
 * Revision 1.2  1995/09/13  14:25:41  pwe
 * tidy for gcc
 *
 * Revision 1.1.1.1  1995/08/14  14:30:25  pwe
 * transferred from DJCH
 *
**********************************************************************/

/* LOG 3/6/93 added extra message to is_fund_dwarf when using
   non-diag libraries djch */
/* LOG 7/9/93 changes for SPARC SVR4.2 to abstract asm directives djch */
/* LOG 25/11/93 renamed SET to DOT_SET to free SET for pwc's use djch */

#include "config.h"
#include "common_types.h"
#include "installtypes.h"
#include "machine.h"
#include "out.h"
#include "shapemacs.h"
#include "expmacs.h"
#include "basicread.h"
#include "xalloc.h"

#include "dwarf_types.h"
#include "dwarf_out.h"
#include "dwarf_queue.h"
#include "dwarf_loc.h"
#include "dwarf_type.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

#define NOT_YET(x) fprintf(stderr,"%s not yet implemented\n",x)

#define BEEN_PUT_OUT(x) ((x)->been_outed != NULL)

#define gcc_FT_long_long		0x8008
#define gcc_FT_unsigned_long_long	0x8208

static int is_fund_dwarf
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  switch(t->key)
  {
   case DIAG_TYPE_ARRAY:
   case DIAG_TYPE_PROC:
   case DIAG_TYPE_STRUCT:
   case DIAG_TYPE_ENUM:
   case DIAG_TYPE_UNION:
    return 0;

   case DIAG_TYPE_FLOAT:
   case DIAG_TYPE_VARIETY:
   case DIAG_TYPE_NULL:
   case DIAG_TYPE_BITFIELD:
    return 1;

   case DIAG_TYPE_LOC:
    return is_fund_dwarf(t->data.loc.object);
   case DIAG_TYPE_PTR:
    return is_fund_dwarf(t->data.ptr.object);
   case DIAG_TYPE_INITED:
    failer("Initialized but undefined diag type in is_fund_dwarf - may be caused by using libraries without diagnostic information");
   case DIAG_TYPE_UNINIT:
   default:
    failer("Illegal diag type in is_fund_dwarf");
  }
  exit (EXIT_FAILURE);
}

static void out_plain_fund_attr
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  switch(t->key)
  {
   case DIAG_TYPE_FLOAT:
    switch(t->data.f_var)	/* magic numbers from install_fns.c */
    {
     case 0:
      dwarf2c(FT_float);
      break;
     case 1:
      dwarf2c(FT_dbl_prec_float);
      break;
     case 2:
      dwarf2c(FT_ext_prec_float);
      break;
     default:
      failer("unknown float type");
      exit(EXIT_FAILURE);
    }
    break;
   case DIAG_TYPE_VARIETY:
    switch(name(t->data.var))
    {
     case scharhd:
      dwarf2c(FT_signed_char);
      break;
     case ucharhd:
      dwarf2c(FT_unsigned_char);
      break;
     case swordhd:
      dwarf2c(FT_signed_short);
      break;
     case uwordhd:
      dwarf2c(FT_unsigned_short);
      break;
     case slonghd:
      dwarf2c(FT_signed_integer);
      break;
     case ulonghd:
      dwarf2c(FT_unsigned_integer);
      break;
     case s64hd:
      dwarf2c(gcc_FT_long_long);
      break;
     case u64hd:
      dwarf2c(gcc_FT_unsigned_long_long);
      break;
     default:
      failer("Unknown int type");
      exit(EXIT_FAILURE);
    }
    break;
   case DIAG_TYPE_BITFIELD:
    out_plain_fund_attr(t->data.bitfield.result_type);
    if (t->data.bitfield.result_type->key != DIAG_TYPE_VARIETY)
      failer("non variety base type in bitfield");
    out_dwarf_bytesize_attr(t->data.bitfield.result_type->data.var);
    OUT_DWARF_ATTR(AT_bit_size);
    dwarf4n((int)t->data.bitfield.no_of_bits.nat_val.small_nat);
    break;
   case DIAG_TYPE_NULL:
    dwarf2c(FT_void);
    break;
   case DIAG_TYPE_PTR:
    if (t->data.ptr.object->key != DIAG_TYPE_NULL)
      failer("non void ptr in out_plain_fund_attr");
    dwarf2c(FT_pointer);
    break;
   default:
    failer("wrong type in out_plain_fund_attr");
    exit(EXIT_FAILURE);
  }
}

static int is_qualified
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  switch(t->key)
  {
   case DIAG_TYPE_LOC:		/* yes if const/volatile */
    if (t->data.loc.qualifier.is_const || t->data.loc.qualifier.is_volatile)
      return 1;
    return is_qualified(t->data.loc.object);
   case DIAG_TYPE_PTR:		/* definit-ish yes */
				/* EXCEPT that pointer to void is
				   DWARF'ed as FT_pointer */
    if (t->data.ptr.qualifier.is_const || t->data.ptr.qualifier.is_volatile)
      return 1;
    if (t->data.ptr.object->key != DIAG_TYPE_NULL)
      return 1;
				/* I dont think that void can be qualified
				 thus we won't recurse to the void*/
   default:
    return 0;
  }
}

static void out_quals
    PROTO_N ( (t) )
    PROTO_T ( diag_tq t )
{
  if (t.is_const)
    dwarf1(MOD_const);
  if (t.is_volatile)
    dwarf1(MOD_volatile);
}

static diag_type dequalify
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
    /* get to base and output mods */
/* QUALIFERS */
  switch (t->key)
  {
   case DIAG_TYPE_LOC:
    out_quals(t->data.loc.qualifier);
    return (dequalify(t->data.loc.object));
   case DIAG_TYPE_PTR:
    if (t->data.ptr.object->key == DIAG_TYPE_NULL)
      return t;			/* NOT a plain diag_type, fudge for void * */
    dwarf1(MOD_pointer_to);
    out_quals(t->data.ptr.qualifier);
				/* qualifiers to the thing being pointed to */
    return (dequalify(t->data.ptr.object));
   default:
    return t;
  }
}

diag_type base_type
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  switch (t->key)
  {
   case DIAG_TYPE_LOC:
    return (base_type(t->data.loc.object));
   case DIAG_TYPE_PTR:
    return (base_type(t->data.ptr.object));
   default:
    return t;
  }
}

static void out_fund_attr
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  if (is_qualified(t))
  {
    OUT_DWARF_ATTR(AT_mod_fund_type);
    new_dwarf_blk2();
    out_plain_fund_attr(dequalify(t));
    leave_dwarf_blk2();
  }
  else
  {
    OUT_DWARF_ATTR(AT_fund_type);
    out_plain_fund_attr((t->key == DIAG_TYPE_LOC) ? t->data.loc.object : t);
  }
}

static void out_plain_user_attr
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  /*  this NEVER writes out the actual TAG_xxxx block, but instead
   outputs the FORM_REF 4 byte offset of the actual block */
  if (!BEEN_PUT_OUT(t))
  {
    failer("out_plain_user_attr without an asm label");
    exit(EXIT_FAILURE);
  }
  dwarf4(&((*t->been_outed)[0]));
}

static void out_user_attr
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  if (is_qualified(t))
  {
    OUT_DWARF_ATTR(AT_mod_u_d_type);
    new_dwarf_blk2();
    out_plain_user_attr(dequalify(t));
    leave_dwarf_blk2();
  }
  else
  {
    OUT_DWARF_ATTR(AT_user_def_type);
    out_plain_user_attr((t->key == DIAG_TYPE_LOC) ? t->data.loc.object : t);
  }
}

static void queue_up_type_out
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  if (BEEN_PUT_OUT(t))
  {
    failer("Whhops, queueing twice");
    return;
  }
  t->been_outed = next_dwarf_type_lab();
  add_type_q(t);
}

void out_dwarf_type_attr
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
				/* output a dwarf type as an attribute
				 if done once already then just the attr,
				 else queue the type, then the attr */
  if (is_fund_dwarf(t))
  {
    out_fund_attr(t);
    return;
  }
  {
    diag_type b = base_type(t);
    if (!BEEN_PUT_OUT(b))
      queue_up_type_out(b);		/* this will assign the label value */

    out_user_attr(t);
    return;
  }
}

void out_dwarf_user_type
    PROTO_N ( (t) )
    PROTO_T ( diag_type t )
{
  if (!BEEN_PUT_OUT(t))		/* if so then no external refs */
  {
    t->been_outed = next_dwarf_type_lab();
  }
  switch(t->key)
  {
   case DIAG_TYPE_ARRAY:
    cont_sib_chain(TAG_array_type);

    OUT_DWARF_ATTR(AT_stride_size);
    out_dwarf_const_by8(t->data.array.stride);
/*    out_dwarf_name_attr(t->data.array.name); */
    {
      OUT_DWARF_ATTR(AT_subscr_data);
      new_dwarf_blk2();
      dwarf1((int)FMT_FT_C_C);
      OUT_DWARF_TAG(FT_signed_integer);
      out_dwarf_const4(t->data.array.lower_b);
      out_dwarf_const4(t->data.array.upper_b); /* FOR C this is one too big */
      dwarf1((int)FMT_ET);
      out_dwarf_type_attr(t->data.array.element_type);
      leave_dwarf_blk2();
    }
    break;
   case DIAG_TYPE_ENUM:
    cont_sib_chain(TAG_enumeration_type);
    out_dwarf_name_attr(TDFSTRING2CHAR(t->data.t_enum.nme));
    if (t->data.t_enum.base_type->key != DIAG_TYPE_VARIETY)
      failer("non integral enum type");
    out_dwarf_bytesize_attr(t->data.t_enum.base_type->data.var);
    OUT_DWARF_ATTR(AT_element_list);
    new_dwarf_blk4();
    {
      int i;
      enum_values * a = t->data.t_enum.values->array;

      for (i=0; i<t->data.t_enum.values->lastused; i++)
      {
	out_dwarf_const4(a[i]->val);
	out_dwarf_string(TDFSTRING2CHAR(a[i]->nme));
      }
    }
    leave_dwarf_blk4();
    break;
   case DIAG_TYPE_PROC:
    cont_sib_chain(TAG_subroutine_type);
    out_dwarf_type_attr(t->data.proc.result_type);
    break;
   case DIAG_TYPE_STRUCT:
    cont_sib_chain(TAG_structure_type);
    out_dwarf_name_attr(TDFSTRING2CHAR(t->data.t_struct.nme));
    out_dwarf_bytesize_attr(t->data.t_struct.tdf_shape);
    break;
   case DIAG_TYPE_UNION:
    cont_sib_chain(TAG_union_type);
    out_dwarf_name_attr(TDFSTRING2CHAR(t->data.t_union.nme));
    out_dwarf_bytesize_attr(t->data.t_union.tdf_shape);
    break;
   default:
    failer("Illegal diag type in out_dwarf_user_type");
  }
				/* now we must set the dwarf type label
				 to be the dwarf label of this block */
  {
    char expr_buf[100];
#if (is80x86)
#define DOT_SET 	".set"
#else
#if (issparc)
#else
error need the .set directive
#endif
#endif

#if FS_CONCAT_STRING
#if (is80x86)
#define SET_F "\t"DOT_SET"\t%s , %s"
#else
#if (issparc)
#define SET_F "\t%s = %s"
#else
error need set format str
#endif
#endif
#else
#if (issparc)
/* KEEP this in step..... */
#define SET_F "\t%s = %s"
#else
#if (is80x86)
#define SET_F "\t.set\t %s , %s"
#else
error write this
#endif
#endif
#endif

#ifdef mips
    sprintf(expr_buf,SET_F,(char *)t->been_outed,
#else
    sprintf(expr_buf,SET_F,(char *)&((t->been_outed)[0]),
#endif
	    current_label_name());
    outs(expr_buf);
    outnl();
  }
  leave_dwarf_blk();

  switch(t->key)
  {
   case DIAG_TYPE_PROC:
    {
      int i;
      diag_type_list pars = t->data.proc.params;

      make_next_new_chain();
      for (i=0; i< pars->lastused; i++)
      {
	cont_sib_chain(TAG_formal_parameter);
	out_dwarf_type_attr(pars->array[i]);
	leave_dwarf_blk();
      }
      if (t->data.proc.opt_args)
      {
	cont_sib_chain(TAG_unspecified_parameters);
	leave_dwarf_blk();
      }
      end_sib_chain();
    }
    break;
   case DIAG_TYPE_STRUCT:
    {
      diag_field_list f = t->data.t_struct.fields;
      int i;

      make_next_new_chain();
      for ( i = f->lastused-1 ;i>=0; i--)
      {
	diag_field m = f->array[i];

	cont_sib_chain(TAG_member);
	out_dwarf_name_attr(TDFSTRING2CHAR(m->field_name));
	out_dwarf_type_attr(m->field_type);
	if (m->field_type->key == DIAG_TYPE_BITFIELD)
	{
				/* dwarf describes bitfields wrt an anonymous
				 object, whose size is that of the base type */
	  int base_type_in_bits =
	    shape_size(m->field_type->data.bitfield.result_type->data.var);
	  int bit_size =
	    m->field_type->data.bitfield.no_of_bits.nat_val.small_nat;
	  int bit_offset_from_base =
	    (int)no(m->where);
	  int bit_offset_in_anon_obj =
	    bit_offset_from_base % base_type_in_bits;
	  int bit_offset_to_anon_obj =
	    bit_offset_from_base - bit_offset_in_anon_obj;

	  OUT_DWARF_ATTR(AT_bit_offset);
	  out_dwarf_thing((int)
#if (little_end)
			  ((base_type_in_bits - /* count from other end  */
			   bit_offset_in_anon_obj) - bit_size)
#else
			  bit_offset_in_anon_obj
#endif
			  ," bits");
	  out_dwarf_bit_member_loc_attr(bit_offset_to_anon_obj);
	}
	else
	  out_dwarf_member_loc_attr(m->where);
	leave_dwarf_blk();
      }
      end_sib_chain();
    }
    break;
   case DIAG_TYPE_UNION:
    {
      diag_field_list f = t->data.t_union.fields;
      int i;

      make_next_new_chain();
      for ( i = f->lastused-1 ;i>=0; i--)
      {
	diag_field m = f->array[i];

	cont_sib_chain(TAG_member);
	out_dwarf_name_attr(TDFSTRING2CHAR(m->field_name));
	out_dwarf_type_attr(m->field_type);
	out_dwarf_member_loc_attr(m->where);
	leave_dwarf_blk();
      }
      end_sib_chain();
    }
    break;
   default:
    break;
  }
}



