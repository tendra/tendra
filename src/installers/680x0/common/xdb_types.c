/*
    		 Crown Copyright (c) 1996

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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/xdb_types.c,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: xdb_types.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:02  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:23  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:02  john
 *
 * Revision 1.2  1996/07/05  14:36:42  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:33  ra
 * Added missing files.
 *
 * Revision 1.4  94/02/21  16:09:42  16:09:42  ra (Robert Andrews)
 * Put in a number of explicit casts.
 *
 * Revision 1.3  93/11/19  16:25:34  16:25:34  ra (Robert Andrews)
 * Bitfields should have the correct size, not 32.
 *
 * Revision 1.2  93/04/19  13:40:05  13:40:05  ra (Robert Andrews)
 * struct_fields and union_fields have been renamed diag_field.
 *
 * Revision 1.1  93/02/22  17:17:29  17:17:29  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include <time.h>
#include "common_types.h"
#include "expmacs.h"
#include "externs.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "shapemacs.h"
#include "utility.h"
#include "xdb_output.h"
#include "xdb_types.h"
#ifndef SEEK_SET
#define SEEK_SET 0
#endif


/*
    GENERATE A UNIQUE IDENTIFIER
*/

static unsigned unique_id
    PROTO_Z ()
{
    static unsigned u = 0 ;
    if ( u == 0 ) {
	time_t t = time ( ( time_t * ) NULL ) ;
	u = ( unsigned ) t ;
    }
    return ( u ) ;
}


/*
    CURRENT POSITIONS IN DIAGNOSTIC NAME TABLES
*/

static posn_t dtposn_local = LOCAL_POSN ;
static posn_t dtposn_globl = GLOBL_POSN ;


/*
    OUTPUT A DIAGNOSTIC DIRECTIVE
*/

posn_t out_dd
    PROTO_N ( ( file, n, loc ) )
    PROTO_T ( FILE *file X int n X int loc )
{
    diag_directive *d = dd + n ;
    long sz = ( diag_format == DIAG_XDB_NEW ? d->new_size : d->old_size ) ;
    posn_t p = ( loc ? dtposn_local : dtposn_globl ) ;
    fprintf ( file, "%s", instr_names [ d->instr ] ) ;
    if ( loc ) {
	dtposn_local = p + sz ;
    } else {
	dtposn_globl = p + sz ;
    }
    return ( p ) ;
}


/*
     CREATE A NEW TABLE POSITION
*/

static table_posn *new_table_posn
    PROTO_N ( ( n, sz ) )
    PROTO_T ( posn_t n X long sz )
{
    table_posn *p ;
    static int no_tp_free = 0 ;
    static table_posn *tp_free ;
    if ( no_tp_free == 0 ) {
	no_tp_free = 20 ;
	tp_free = alloc_nof ( table_posn, no_tp_free ) ;
    }
    p = tp_free++ ;
    no_tp_free-- ;
    p->is_lab = 0 ;
    p->posn = n ;
    p->size = sz ;
    return ( p ) ;
}


/*
    OUTPUT A TABLE POSITION
*/

void out_posn
    PROTO_N ( ( file, p, comma ) )
    PROTO_T ( FILE *file X table_posn *p X int comma )
{
    if ( p->is_lab ) {
	fprintf ( file, "LD%d", ( int ) p->posn ) ;
    } else {
	fprintf ( file, "0x%x", ( unsigned int ) p->posn ) ;
    }
    fputc ( ( comma ? ',' : '\n' ), file ) ;
    return ;
}


/*
    GO TO A POSITION IN A FILE AND PRINT A TABLE POSITION
*/

void fill_gap
    PROTO_N ( ( file, fp, t ) )
    PROTO_T ( FILE *file X long fp X posn_t t )
{
    long fp_old = ftell ( file ) ;
    if ( fseek ( file, fp, SEEK_SET ) == -1 ) {
	error ( "Internal file seek error" ) ;
	return ;
    }
    fprintf ( file, "0x%x", ( unsigned int ) t ) ;
    if ( fseek ( file, fp_old, SEEK_SET ) == -1 ) {
	error ( "Internal file seek error" ) ;
    }
    return ;
}


/*
    CURRENT DIAGNOSTICS LABEL NUMBER
*/

static long diag_lab = 0 ;


/*
    FIND THE TABLE POSITION OF A TDF SHAPE
*/

static table_posn *analyse_diag_shape
    PROTO_N ( ( file, sha ) )
    PROTO_T ( FILE *file X shape sha )
{
    posn_t t = NULL_POSN ;
    long sz = shape_size ( sha ) ;
    switch ( name ( sha ) ) {
	case scharhd : t = CHAR_POSN + sz ; break ;
	case swordhd :
	case slonghd : t = SIGNED_POSN + sz ; break ;
	case ucharhd :
	case uwordhd :
	case ulonghd : t = UNSIGNED_POSN + sz ; break ;
	case shrealhd :
	case realhd :
	case doublehd : t = FLOATING_POSN + sz ; break ;
    }
    return ( new_table_posn ( t, sz ) ) ;
}


/*
    FIND THE TABLE POSITION OF A DIAGNOSTIC TYPE
*/

table_posn *analyse_diag_type
    PROTO_N ( ( file, dt, loc ) )
    PROTO_T ( FILE *file X diag_type dt X int loc )
{
    table_posn *res ;
    if ( dt->been_outed ) return ( ( table_posn * ) dt->been_outed ) ;

    switch ( dt->key ) {

	case DIAG_TYPE_ARRAY : {
	    diag_type dtl = dt->data.array.element_type ;
	    long lo = no ( dt->data.array.lower_b ) ;
	    long hi = no ( dt->data.array.upper_b ) ;

	    table_posn *p = analyse_diag_type ( file, dtl, loc ) ;
	    long sz = ( hi - lo + 1 ) * ( p->size ) ;
	    posn_t s, t = out_dd ( file, xdb_subrange, loc ) ;

	    if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "0,0," ) ;
	    fprintf ( file, "%ld,%ld,0x%x,32\n", lo, hi,
		      ( unsigned int ) ( SIGNED_POSN + 32 ) ) ;
	    s = out_dd ( file, xdb_array, loc ) ;
	    if ( diag_format == DIAG_XDB_NEW ) {
		fprintf ( file, "0,0,0,0,0,0," ) ;
	    }
	    fprintf ( file, "0,%ld,0x%x,", sz, ( unsigned int ) t ) ;
	    if ( diag_format == DIAG_XDB_NEW ) {
		out_posn ( file, p, 1 ) ;
		fprintf ( file, "%ld\n", p->size ) ;
	    } else {
		out_posn ( file, p, 0 ) ;
	    }
	    res = new_table_posn ( s, sz ) ;
	    break ;
	}

	case DIAG_TYPE_BITFIELD : {
	    long sz = dt->data.bitfield.no_of_bits.nat_val.small_nat ;
	    res = new_table_posn ( SIGNED_POSN + 32, sz ) ;
	    break ;
	}

	case DIAG_TYPE_ENUM : {
	    char *nm = dt->data.t_enum.nme.ints.chars ;
	    enum_values *fld = dt->data.t_enum.values->array ;
	    long i, n = ( long ) dt->data.t_enum.values->lastused ;

	    /* Initialize enumeration information */
	    long fp ;
	    posn_t t ;
	    t = out_dd ( file, xdb_enum, loc ) ;
	    fp = ftell ( file ) ;
	    fprintf ( file, "%s,32\n", NULL_POSN_STR ) ;
	    res = new_table_posn ( t, L32 ) ;

	    /* Deal with enumeration members */
	    for ( i = n - 1 ; i >= 0 ; i-- ) {
		char *fnm = fld [i]->nme.ints.chars ;
		long v = no ( fld [i]->val ) ;
		posn_t s = out_dd ( file, xdb_memenum, loc ) ;
		fill_gap ( file, fp, s ) ;
		if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "0," ) ;
		if ( *fnm ) {
		    diag_string ( file, fnm ) ;
		} else {
		    diag_string ( file, "__unknown" ) ;
		}
		fprintf ( file, ",%ld,", v ) ;
		fp = ftell ( file ) ;
		fprintf ( file, "%s\n", NULL_POSN_STR ) ;
	    }

	    /* Round off enumeration definition */
	    if ( *nm ) {
		( void ) out_dd ( file, xdb_tagdef, loc ) ;
		fprintf ( file, "0," ) ;
		if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "1," ) ;
		diag_string ( file, nm ) ;
		fprintf ( file, "," ) ;
		out_posn ( file, res, 0 ) ;
	    }
	    break ;
	}

	case DIAG_TYPE_FLOAT : {
	    shape sha = f_floating ( dt->data.f_var ) ;
	    res = analyse_diag_shape ( file, sha ) ;
	    break ;
	}

	case DIAG_TYPE_LOC : {
	    diag_type dtl = dt->data.loc.object ;
	    res = analyse_diag_type ( file, dtl, loc ) ;
	    break ;
	}

	case DIAG_TYPE_NULL : {
	    res = new_table_posn ( NULL_POSN, L0 ) ;
	    break ;
	}

	case DIAG_TYPE_PROC : {
	    diag_type dtl = dt->data.proc.result_type ;
	    table_posn *p = analyse_diag_type ( file, dtl, loc ) ;
	    posn_t t = out_dd ( file, xdb_functype, loc ) ;
	    if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "0,0," ) ;
	    fprintf ( file, "32," ) ;
	    out_posn ( file, p, 1 ) ;
	    fprintf ( file, "%s\n", NULL_POSN_STR ) ;
	    res = new_table_posn ( t, L32 ) ;
	    break ;
	}

	case DIAG_TYPE_PTR : {
	    diag_type dtl = dt->data.ptr.object ;
	    table_posn *p = analyse_diag_type ( file, dtl, loc ) ;
	    posn_t t = out_dd ( file, xdb_pointer, loc ) ;
	    out_posn ( file, p, 1 ) ;
	    fprintf ( file, "32\n" ) ;
	    res = new_table_posn ( t, L32 ) ;
	    break ;
	}

	case DIAG_TYPE_STRUCT : {
	    shape sha = dt->data.t_struct.tdf_shape ;
	    long sz = shape_size ( sha ) ;
	    char *nm = dt->data.t_struct.nme.ints.chars ;
#if 0
	    struct_fields *fld = dt->data.t_struct.fields->array ;
#else
	    diag_field *fld = dt->data.t_struct.fields->array ;
#endif
	    long i, n = ( long ) dt->data.t_struct.fields->lastused ;

	    /* Initialize structure information */
	    long fp ;
	    posn_t t ;
	    int taglab = 0 ;
	    char nmbuff [50] ;
	    long dlab = diag_lab++ ;
	    if ( diag_format == DIAG_XDB_NEW ) {
		if ( *nm == 0 ) {
		    unsigned u = unique_id () ;
		    nm = nmbuff ;
		    sprintf ( nm, "(%u.%ld)", u, dlab ) ;
		}
		taglab = 1 ;
	    }
	    if ( !taglab ) fprintf ( file, "LD%ld:", dlab ) ;
	    t = out_dd ( file, xdb_struct, loc ) ;
	    fprintf ( file, "0," ) ;
	    fp = ftell ( file ) ;
	    fprintf ( file, "%s,%s,%s,%ld\n", NULL_POSN_STR, NULL_POSN_STR,
		      NULL_POSN_STR, sz ) ;
	    res = new_table_posn ( t, sz ) ;

	    /* Print tag information */
	    if ( *nm ) {
		posn_t tt ;
		if ( taglab ) fprintf ( file, "LD%ld:", dlab ) ;
		tt = out_dd ( file, xdb_tagdef, loc ) ;
		fprintf ( file, "0," ) ;
		if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "1," ) ;
		diag_string ( file, nm ) ;
		fprintf ( file, "," ) ;
		out_posn ( file, res, 0 ) ;
		if ( taglab ) t = tt ;
	    }

	    /* Set up structure label */
	    res->is_lab = 1 ;
	    res->posn = ( posn_t ) dlab ;
	    dt->been_outed = ( OUTPUT_REC ) res ;

	    /* Deal with structure fields */
	    for ( i = n - 1 ; i >= 0 ; i-- ) {
		char *fnm = fld [i]->field_name.ints.chars ;
		long off = no ( fld [i]->where ) ;
		diag_type dtl = fld [i]->field_type ;
		table_posn *q = analyse_diag_type ( file, dtl, loc ) ;
		posn_t s = out_dd ( file, xdb_field, loc ) ;
		fill_gap ( file, fp, s ) ;
		if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "0,0," ) ;
		if ( *fnm ) {
		    diag_string ( file, fnm ) ;
		} else {
		    diag_string ( file, "__unknown" ) ;
		}
		fprintf ( file, ",%ld,", off ) ;
		out_posn ( file, q, 1 ) ;
		fprintf ( file, "%ld,", q->size ) ;
		fp = ftell ( file ) ;
		fprintf ( file, "%s\n", NULL_POSN_STR ) ;
	    }

	    /* Round off structure definition */
	    res->is_lab = 0 ;
	    res->posn = t ;
	    break ;
	}

	case DIAG_TYPE_UNION : {
	    shape sha = dt->data.t_union.tdf_shape ;
	    long sz = shape_size ( sha ) ;
	    char *nm = dt->data.t_union.nme.ints.chars ;
#if 0
	    union_fields *fld = dt->data.t_union.fields->array ;
#else
	    diag_field *fld = dt->data.t_union.fields->array ;
#endif
	    long i, n = ( long ) dt->data.t_union.fields->lastused ;

	    /* Initialize union information */
	    long fp ;
	    posn_t t ;
	    int taglab = 0 ;
	    long dlab = diag_lab++ ;
	    char nmbuff [50] ;
	    if ( diag_format == DIAG_XDB_NEW ) {
		if ( *nm == 0 ) {
		    unsigned u = unique_id () ;
		    nm = nmbuff ;
		    sprintf ( nm, "(%u.%ld)", u, dlab ) ;
		}
		taglab = 1 ;
	    }
	    if ( !taglab ) fprintf ( file, "LD%ld:", dlab ) ;
	    t = out_dd ( file, xdb_union, loc ) ;
	    fp = ftell ( file ) ;
	    fprintf ( file, "%s,%ld\n", NULL_POSN_STR, sz ) ;
	    res = new_table_posn ( t, sz ) ;

	    /* Print tag information */
	    if ( *nm ) {
		posn_t tt ;
		if ( taglab ) fprintf ( file, "LD%ld:", dlab ) ;
		tt = out_dd ( file, xdb_tagdef, loc ) ;
		fprintf ( file, "0," ) ;
		if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "1," ) ;
		diag_string ( file, nm ) ;
		fprintf ( file, "," ) ;
		out_posn ( file, res, 0 ) ;
		if ( taglab ) t = tt ;
	    }

	    /* Set up union label */
	    res->is_lab = 1 ;
	    res->posn = ( posn_t ) dlab ;
	    dt->been_outed = ( OUTPUT_REC ) res ;

	    /* Deal with union fields */
	    for ( i = n - 1 ; i >= 0 ; i-- ) {
		char *fnm = fld [i]->field_name.ints.chars ;
		long off = no ( fld [i]->where ) ;
		diag_type dtl = fld [i]->field_type ;
		table_posn *q = analyse_diag_type ( file, dtl, loc ) ;
		posn_t s = out_dd ( file, xdb_field, loc ) ;
		fill_gap ( file, fp, s ) ;
		if ( diag_format == DIAG_XDB_NEW ) fprintf ( file, "0,0," ) ;
		if ( *fnm ) {
		    diag_string ( file, fnm ) ;
		} else {
		    diag_string ( file, "__unknown" ) ;
		}
		fprintf ( file, ",%ld,", off ) ;
		out_posn ( file, q, 1 ) ;
		fprintf ( file, "%ld,", q->size ) ;
		fp = ftell ( file ) ;
		fprintf ( file, "%s\n", NULL_POSN_STR ) ;
	    }

	    /* Round off union definition */
	    res->is_lab = 0 ;
	    res->posn = t ;
	    break ;
	}

	case DIAG_TYPE_VARIETY : {
	    shape sha = f_integer ( dt->data.var ) ;
	    res = analyse_diag_shape ( file, sha ) ;
	    break ;
	}

	default : {
	    res = new_table_posn ( NULL_POSN, L0 ) ;
	    break ;
	}
    }

    dt->been_outed = ( OUTPUT_REC ) res ;
    return ( res ) ;
}


/*
    DIAGNOSTIC SCOPE STACK
*/

static dscope *dscope_stack = null ;
static int no_dscope = 0 ;
static int dscope_stk_size = 0 ;


/*
    PUSH A DIAGNOSTICS SCOPE
*/

void push_dscope
    PROTO_N ( ( p, t ) )
    PROTO_T ( posn_t p X int t )
{
    int n = no_dscope++ ;
    if ( n >= dscope_stk_size ) {
	dscope_stk_size += 20 ;
	dscope_stack = realloc_nof ( dscope_stack, dscope, dscope_stk_size ) ;
    }
    dscope_stack [n].posn = p ;
    dscope_stack [n].dscope_type = t ;
    return ;
}


/*
    POP A DIAGNOSTICS SCOPE
*/

dscope *pop_dscope
    PROTO_Z ()
{
    int n = no_dscope ;
    if ( n == 0 ) return ( null ) ;
    no_dscope = ( --n ) ;
    return ( dscope_stack + n ) ;
}
