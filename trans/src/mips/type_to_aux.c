/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Contains procedure long add_type_to_aux(diag_type s, long ind) which
 * converts a TDF shape into an AUXU (see sym.h) and adds it to the auxillary
 * table for the file number given as parameter as required by the MIPS
 * symbol table.
 *
 * If the entry generated is greater than 1 AUXU in length the index
 * corresponding to the first entry made is returned.
 */

#include <shared/xalloc.h>

#include <local/expmacs.h>

#include "cross_config.h"

#include <symtab/symconst.h>
#include <symtab/symtab.h>

#include <reader/codetypes.h>
#include <reader/basicread.h>

#include <construct/shapemacs.h>
#include <construct/exp.h>

#include <diag/diagtypes.h>
#include <diag/diag_fns.h>

#include "diag_out.h"
#include "type_to_aux.h"

extern long mainfile;

int field=0;

long
set_tq(int qual, TIR *type, long ind)
{
    AUXU retaux;
    long index=0;
    switch (field++)	{
		case 0: break;
		case 1: type->tq1=type->tq0;
			break;
		case 2: type->tq2=type->tq1;
			type->tq1=type->tq0;
			break;
		case 3: type->tq3=type->tq2;
			type->tq2=type->tq1;
			type->tq1=type->tq0;
			break;
		case 4: type->tq4=type->tq3;
			type->tq3=type->tq2;
			type->tq2=type->tq1;
			type->tq1=type->tq0;
			break;
		case 5: type->tq5=type->tq4;
			type->tq4=type->tq3;
			type->tq3=type->tq2;
			type->tq2=type->tq1;
			type->tq1=type->tq0;
			break;
		case 6:	type->continued=1;
			retaux.ti=(*type);
			index=add_aux(retaux, ind);
			type=(TIR*)xcalloc(1,sizeof(TIR));
			type->tq0=qual;
			field=1;
			return index;
		}
    type->tq0=qual;
    return -1;
}

long
type_size(diag_type dt)
{
    switch(dt->key) {
	case DIAG_TYPE_VARIETY: {
	   return shape_size(dt->data.var);
	}
	case DIAG_TYPE_STRUCT: case DIAG_TYPE_UNION: {
	   return shape_size(dt->data.t_struct.tdf_shape);
	}
	case DIAG_TYPE_FLOAT: {
		return (dt->data.f_var)?64:32;
	}
	case DIAG_TYPE_ARRAY: {
		long is = type_size(dt->data.array.element_type);
		return is *(dt->data.array.upper_b-dt->data.array.lower_b+1);
	}
	case DIAG_TYPE_ENUM: {
		return type_size(dt->data.t_enum.base_type);
	}
	default: return 32;
    }
}

long
add_type_to_aux(diag_type dt, long ind)
{
    TIR* type=(TIR*)xcalloc(1,sizeof(TIR));
    long firstind= -1;
    int dimension=0;
    int elemsize=0;
    int scale=1;
    diag_type xdt = dt;
    AUXU maxaux, retaux;
    maxaux.isym=0xffffffff;
    field=0;
    if (dt == (diag_type)0) {
	return 1048575;
    }

    {type->bt=63;
     while (type->bt==63)
     {
        if (dt == (diag_type)0) {
           type->bt = btNil;
  	   retaux.ti=(*type);
	   break;
	}
	switch (dt->key)
	{
	case DIAG_TYPE_BITFIELD: {
          type->bt=btUInt;
          type->fBitfield=1;
          retaux.ti = *type;
          firstind = add_aux(retaux, ind);
          retaux.rndx.rfd = dt->data.bitfield.no_of_bits.nat_val.small_nat;
          retaux.rndx.index=0;
          add_aux(retaux, ind);
          break;
        }
	case DIAG_TYPE_UNINIT:  case DIAG_TYPE_NULL: case DIAG_TYPE_INITED:
	   type->bt = btNil;
  	   retaux.ti=(*type);
	   break;
	case DIAG_TYPE_VARIETY: {
	  switch (name(dt->data.var)) {
            case scharhd:
               type->bt = btChar;
               retaux.ti=(*type);
               break;
            case ucharhd:
               type->bt = btUChar;
               retaux.ti=(*type);
               break;
            case swordhd:
               type->bt = btShort;
               retaux.ti=(*type);
               break;
            case uwordhd:
               type->bt = btUShort;
               retaux.ti=(*type);
               break;
            case slonghd:
               type->bt = btInt;
               retaux.ti=(*type);
               break;
            case ulonghd:
               type->bt = btUInt;
               retaux.ti=(*type);
               break;
            default: failer("DIAGS - not variety ");
          }
          break;
        }
        case DIAG_TYPE_FLOAT: {
          if (dt->data.f_var == 0) {
           	type->bt = btFloat;
          }
          else {
           	type->bt = btDouble;
           }
  	   retaux.ti=(*type);
	   break;
	}

	case DIAG_TYPE_PROC: {
   /* ???  MIPS   ???  should use result type ???  */
          set_tq(tqProc, type, ind);
          type->bt = btUInt;
          retaux.ti=(*type);
          break;
	}
	case DIAG_TYPE_PTR: {
           firstind= set_tq(tqPtr, type, ind);
	   dt = dt->data.ptr.object;
	   break;
	}
	case DIAG_TYPE_STRUCT: case DIAG_TYPE_UNION: {
           type->bt = (dt->key == DIAG_TYPE_STRUCT)? btStruct:btUnion;
	   retaux.ti = *type;
	   if (firstind==-1)
		{firstind=add_aux(retaux, ind);}
	   else	{add_aux(retaux, ind);}
	   retaux.rndx.rfd = mainfile;
	   retaux.rndx.index=find_aux(dt);
	   add_aux(retaux,ind);
	   retaux.rndx.rfd = mainfile;
	   retaux.rndx.index=0;
	   break;
	}
	case DIAG_TYPE_ARRAY: {
	   diag_type ndt = dt->data.array.element_type;
	   firstind=set_tq(tqArray, type, ind);
	   dimension=1;
	   xdt = dt;

	   while (ndt->key==DIAG_TYPE_ARRAY) {
		dimension++;
		ndt = ndt->data.array.element_type;
	   }
	   dt = ndt;
	   elemsize = type_size(ndt)>>3;
	   break;
	}
	case DIAG_TYPE_ENUM: case DIAG_TYPE_LOC: {
	    dt= dt->data.t_enum.base_type;
	    break;
	}
	default:
         failer ("bad diagnostics type");
         break;
	};
     }
  }


	if (firstind==-1)
	   {firstind=add_aux(retaux,ind);
	   }
	else
	   {add_aux(retaux,ind);
	   }

	while (dimension--) {
          int i;
          diag_type ndt = xdt;
          for (i=1;i<dimension;i++) {
              ndt = ndt->data.array.element_type;
          }
          i = no(ndt->data.array.upper_b) - no(ndt->data.array.lower_b)+1;
          retaux.rndx.rfd = 4095;
          retaux.rndx.index=4;
          add_aux(retaux,ind);
          retaux.rndx.rfd = mainfile;
          retaux.rndx.index=0;
          add_aux(retaux,ind);
          retaux.dnLow = no(ndt->data.array.lower_b);
          add_aux(retaux,ind);
          retaux.dnHigh = no(ndt->data.array.upper_b);
          add_aux(retaux,ind);
          retaux.width = elemsize*scale;
          scale =i*scale;
          add_aux(retaux,ind);
	}

    return firstind;
    /* return index of first element added to the AUX table */
}
