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


/* linux/diag_out.c */

/**********************************************************************
$Author: release $
$Date: 1998/03/27 09:47:49 $
$Revision: 1.2 $
$Log: diag_out.c,v $
 * Revision 1.2  1998/03/27  09:47:49  release
 * Changes for 4.1.2 release.
 *
 * Revision 1.1.1.1  1998/02/25  12:32:45  release
 * Initial version
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.12  1997/04/02  10:33:21  pwe
 * diagnose pl_tests
 *
 * Revision 1.11  1997/03/24  12:43:26  pwe
 * outn int->long
 *
 * Revision 1.10  1996/10/29  14:55:32  pwe
 * correct linux/elf stabs for global variables
 *
 * Revision 1.9  1996/07/05  09:07:43  pwe
 * correct stabs enums
 *
 * Revision 1.8  1996/05/09  17:30:47  pwe
 * shift invalidate_dest, and stabs postlude
 *
 * Revision 1.7  1996/04/19  16:14:16  pwe
 * simplified use of global id = id, correcting linux call problem
 *
 * Revision 1.6  1996/03/13  13:43:26  pwe
 * diags for long long
 *
 * Revision 1.5  1996/02/08  13:45:29  pwe
 * Linux elf v aout option
 *
 * Revision 1.4  1995/12/20  11:13:54  pwe
 * stabs local variable scopes
 *
 * Revision 1.3  1995/11/30  10:19:43  pwe
 * diag struct struct
 *
 * Revision 1.2  1995/03/28  14:28:53  pwe
 * correct diagnose empty file
 *
 * Revision 1.1  1995/03/17  18:29:52  pwe
 * stabs diagnostics for solaris and linux
 *
**********************************************************************/

#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "out.h"
#include "machine.h"
#include "shapemacs.h"
#include "expmacs.h"
#include "tags.h"
#include "szs_als.h"
#include "diagglob.h"
#include "xalloc.h"
#include "exp.h"
#include "mark_scope.h"
#include "externs.h"
#ifdef NEWDIAGS
#include "codermacs.h"
#include "instr.h"
#endif



/*
    FORWARD DECLARATIONS
*/

static void stab_scope_open PROTO_S ( ( long ) ) ;
static void stab_scope_close PROTO_S ( ( long ) ) ;
static void stab_file PROTO_S ( ( long, bool ) ) ;
static void stab_local PROTO_S ( ( diag_info *, int, exp ) ) ;
static void stab_types PROTO_S ( ( void ) ) ;




/*
    DIAGNOSTICS FILE
*/

static FILE *dg_file ;
static char *dg_file_name ;


/*
    BASIC TYPE NUMBERS
*/

#define STAB_SCHAR	4
#define STAB_UCHAR	6
#define STAB_SSHRT	2
#define STAB_USHRT	3
#define STAB_SLONG	1
#define STAB_ULONG	8
#define STAB_FLOAT	10
#define STAB_DBL	11
#define STAB_LDBL	12
#define STAB_VOID	13
#define STAB_S64	14
#define STAB_U64	15
#define NO_STABS	16


/*
    80x86 register numbers
*/

#ifdef NEWDIAGS
static long reg_stabno [8] = {0, 2, 1, 3, 7, 6, 5, 4};
#endif

/*
    BASIC POINTERS
*/

static long stab_ptrs [ NO_STABS ] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
} ;


/*
    CURRENT TYPE NUMBER
*/

static long typeno ;


/*
    SIZE OF LAST STAB TYPE OUTPUT
*/

static long last_type_sz = 0 ;


/*
    CURRENT LINE NUMBER AND FILE NUMBER
*/

long currentlno = -1 ;
long currentfile = -1 ;


/*
    ARRAY OF TYPE SIZES
*/

static long *type_sizes ;
static int total_type_sizes = 0 ;


/*
    SETTING AND GETTING TYPE SIZES
*/

#define set_stab_size( i )	type_sizes [ ( i ) ] = last_type_sz
#define get_stab_size( i )	( type_sizes [ ( i ) ] )


/*
    GET THE NEXT TYPE NUMBER
*/

static long next_typen
    PROTO_Z ()
{
    if ( typeno >= total_type_sizes ) {
	int i, n = total_type_sizes, m = n + 100 ;
	type_sizes = ( long * ) xrealloc ( (void*)(CH type_sizes),
					m * sizeof ( long ) ) ;
	for ( i = n ; i < m ; i++ ) type_sizes [i] = 0 ;
	total_type_sizes = m ;
    }
    return ( typeno++ ) ;
}


/*
    ARRAY OF FILE DESCRIPTORS
*/

static filename *fds = NULL ;
static int szfds = 0 ;
static int nofds = 0 ;


/*
    ADD A NEW FILE TO THE ARRAY OF FILE DESCRIPTORS
*/

void stab_collect_files
    PROTO_N ( (f) )
    PROTO_T ( filename f )
{
    if ( fds == NULL ) {
	szfds += 10 ;
	fds = ( filename * ) xmalloc ( szfds * sizeof ( filename ) ) ;
    } else if ( nofds >= szfds ) {
	szfds += 10 ;
	fds = ( filename * ) xrealloc ( (void*)(CH fds),
				szfds * sizeof ( filename ) ) ;
    }
    fds [ nofds++ ] = f ;
    return ;
}


/*
    FIND THE FILE DESCRIPTOR CORRESPONDING TO A FILE NAME
*/

static long find_file
    PROTO_N ( (f) )
    PROTO_T ( char * f )
{
    long i ;
    for ( i = 0 ; i < nofds ; i++ ) {
	if ( strcmp ( f, fds [i]->file.ints.chars ) == 0 ) return ( i ) ;
    }
    return ( 0 ) ;
}


static int last_proc_cname;
static char * last_proc_pname;
static int in_proc = 0;

static void out_procname
    PROTO_Z ()
{
  if (last_proc_cname == -1) {
    outs (last_proc_pname);
  }
  else {
    outs(local_prefix);
    outn ((long)last_proc_cname);
  };
}


/*
    OUTPUT A FILE POSITION CONSTRUCT
*/

#define N_SLINE 0x44
#define N_DSLINE 0x46
#define N_BSLINE 0x48
#define N_LBRAC  0xc0
#define N_RBRAC  0xe0

static void stabd
    PROTO_N ( (findex, lno, seg) )
    PROTO_T ( long findex X long lno X int seg )
{
    long i ;

    if ( findex == currentfile && lno == currentlno ) return ;
    stab_file ( findex, 1 ) ;

    if (seg != 0)		/* 0 suppresses always */
    {
      if (seg < 0 && !linux_elf)
	seg = - seg;
      if (seg > 0)		/* -ve line nos are put out in the stabs */
      {
	i = next_lab () ;
	fprintf ( dg_file, "%sL.%ld:\n", local_prefix, i ) ;
	fprintf ( dg_file, "\t.stabn\t0x%x,0,%ld,%sL.%ld",seg, lno, local_prefix, i ) ;
	if (linux_elf && in_proc) {
	  outs ("-");
	  out_procname ();
	}
	outnl ();
      }
    }
    currentlno = lno ;
    return ;
}


#ifdef NEWDIAGS
/*
    OUTPUT DIAGNOSTICS SURROUNDING CODE
*/

void code_diag_info
    PROTO_N ( (d, proc_no, mcode, args) )
    PROTO_T ( diag_info * d X int proc_no X void (*mcode) PROTO_S ((void *)) X void * args )
{
  if (d == nildiag) {
    (*mcode)(args);
    return;
  }
  switch (d->key) {
    case DIAG_INFO_SCOPE: {
	stab_scope_open ( currentfile ) ;
	stabd ( currentfile, ( long ) ( currentlno + 1 ), N_SLINE ) ;
	code_diag_info (d->more, proc_no, mcode, args);
	stab_scope_close ( currentfile ) ;
	return;
    }
    case DIAG_INFO_SOURCE: {
	sourcemark *s = &d->data.source.beg ;
	long f = find_file ( s->file->file.ints.chars ) ;
	stabd ( f, ( long ) s->line_no.nat_val.small_nat ,N_SLINE) ;
	code_diag_info (d->more, proc_no, mcode, args);
	s = &d->data.source.end ;
	f = find_file ( s->file->file.ints.chars ) ;
	stabd ( f, ( long ) s->line_no.nat_val.small_nat ,N_SLINE) ;
	return;
    }
    case DIAG_INFO_ID: {
	exp acc = d -> data.id_scope.access;
	if (name(acc) != hold_tag)
	  failer("not hold_tag");
	acc = son(acc);
	if (name(acc) == cont_tag && name(son(acc)) == name_tag && isvar(son(son(acc))))
	  acc = son(acc);
	if ( ( name(acc) == name_tag && !isdiscarded(acc) && !isglob(son(acc)) ) ||
		name(acc) == val_tag )
	  stab_local ( d, proc_no, acc );
	code_diag_info (d->more, proc_no, mcode, args);
    }
  };
  return;
}


#else

/*
    OUTPUT INITIAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void output_diag
    PROTO_N ( (d, proc_no, e) )
    PROTO_T ( diag_info * d X int proc_no X exp e )
{
  if ( d->key == DIAG_INFO_SOURCE ) {
    sourcemark *s = &d->data.source.beg ;
    long f = find_file ( s->file->file.ints.chars ) ;
    stabd ( f, ( long ) s->line_no.nat_val.small_nat ,N_SLINE) ;
    return ;
  }

  if (d -> key == DIAG_INFO_ID) {
    exp acc = d -> data.id_scope.access;

    if ( isglob ( son ( acc ) ) || no ( son ( acc ) ) == 1 ) return;
    mark_scope(e);

    if ( props ( e ) & 0x80 ) {
      stab_scope_open ( currentfile ) ;
      stabd ( currentfile, ( long ) ( currentlno + 1 ), N_SLINE ) ;
    }

    stab_local ( d, proc_no, acc );
    return ;
  }
}


/*
    OUTPUT FINAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void output_end_scope
    PROTO_N ( (d, e) )
    PROTO_T ( diag_info * d X exp e )
{
    if ( d->key == DIAG_INFO_SOURCE ) {
	sourcemark *s = &d->data.source.end ;
	long f = find_file ( s->file->file.ints.chars ) ;
	long lno = s->line_no.nat_val.small_nat ;
	stabd ( f, lno, N_SLINE) ;
	return ;
    }
    if ( d->key == DIAG_INFO_ID && props ( e ) & 0x80 ) {
	stab_scope_close ( currentfile ) ;
	return ;
    }
    return ;
}


#endif
/*
    INITIALISE DIAGNOSTICS
*/

void out_diagnose_prelude
    PROTO_Z ()
{
    dg_file_name = tmpnam ( NULL ) ;
    dg_file = fopen ( dg_file_name, "w" ) ;
    if ( dg_file == NULL ) {
	failer ( "Can't open temporary diagnostics file" ) ;
	exit (EXIT_FAILURE) ;
    }
    stab_types () ;
    return ;
}


/*
    INITIALIZE DIAGNOSTICS
*/

void init_stab_aux
    PROTO_Z ()
{
    int c ;
    FILE *f ;
    int i, j = -1 ;
    for ( i = 0 ; i < nofds ; i++ ) {
	char *s = fds [i]->file.ints.chars ;
	int n = ( int ) strlen ( s ) ;
	if ( n && s [ n - 1 ] != 'h' ) j = i ;
    }
    fclose ( dg_file ) ;
    dg_file = fpout ;
    if (j >= 0)
	fprintf (dg_file, "\t.file\t\"%s\"\n", fds[j]->file.ints.chars) ;
    else
	fprintf (dg_file, "\t.file\t\"no_source_file\"\n") ;
    stab_file ( ( long ) j, 0 ) ;
    f = fopen ( dg_file_name, "r" ) ;
    if ( f == NULL ) {
	failer ( "Can't open temporary diagnostics file" ) ;
	exit (EXIT_FAILURE) ;
    }
    while ( c = fgetc ( f ), c != EOF ) outc ( c ) ;
    fclose ( f ) ;
    remove ( dg_file_name ) ;
    return ;
}

void out_diagnose_postlude
    PROTO_Z ()
{
    long i = next_lab () ;
    fprintf ( dg_file, ".text\n" ) ;
    fprintf ( dg_file, "%sL.%ld:\n", local_prefix, i ) ;
    fprintf ( dg_file, "\t.stabs\t\"\",0x64,0,0,%sL.%ld\n", local_prefix, i ) ;
    return ;
}


/*
    FIND THE STAB OF A SIMPLE SHAPE
*/

static long out_sh_type
    PROTO_N ( (s) )
    PROTO_T ( shape s )
{
    last_type_sz = shape_size ( s ) ;
    switch ( name ( s ) ) {
	case scharhd : return ( STAB_SCHAR ) ;
	case ucharhd : return ( STAB_UCHAR ) ;
	case swordhd : return ( STAB_SSHRT ) ;
	case uwordhd : return ( STAB_USHRT ) ;
	case slonghd : return ( STAB_SLONG ) ;
	case ulonghd : return ( STAB_ULONG ) ;
	case s64hd : return ( STAB_S64 ) ;
	case u64hd : return ( STAB_U64 ) ;
	case shrealhd : return ( STAB_FLOAT ) ;
	case realhd : return ( STAB_DBL ) ;
	case doublehd : return ( STAB_LDBL ) ;
    }
    return ( STAB_VOID ) ;
}


/*
    OUTPUT DIAGNOSTICS DIRECTIVE FOR A FILE
*/

static void stab_file
    PROTO_N ( (findex, internal) )
    PROTO_T ( long findex X bool internal )
{
    static long i = 0 ;

    if ( findex == currentfile || findex < 0 || findex >= szfds ) {
	return ;
    }

    if ( !internal ) {
	/* source file */
	i = next_lab () ;
	fprintf ( dg_file, "%sL.%ld:\n", local_prefix, i ) ;
	fprintf ( dg_file, "\t.stabs\t\"%s\",0x64,0,0,%sL.%ld\n",
		  fds [ findex ]->file.ints.chars, local_prefix, i ) ;
    } else {
	/* included file */
	fprintf ( dg_file, "\t.stabs\t\"%s\",0x84,0,0,%sL.%ld\n",
		  fds [ findex ]->file.ints.chars, local_prefix, i ) ;
    }
    currentfile = findex ;
    return ;
}


/*
    ARRAY OF DIAGNOSTIC SCOPES
*/

static long open_label = 0 ;
static long bracket_level = 0 ;


/*
    START OF A DIAGNOSTICS SCOPE
*/

static void stab_scope_open
    PROTO_N ( (findex) )
    PROTO_T ( long findex )
{
    long i ;
    stab_file ( findex, 1 ) ;
    if ( open_label != 0 )
    {
	fprintf ( dg_file, "\t.stabn\t0x%x,0,%ld,%sL.%ld\n", N_LBRAC,
		  bracket_level, local_prefix, open_label ) ;
    }
    i = next_lab () ;
    fprintf ( dg_file, "%sL.%ld:\n", local_prefix, i ) ;
    bracket_level++ ;
    open_label = i ;
    return ;
}


/*
    END OF A DIAGNOSTICS SCOPE
*/

static void stab_scope_close
    PROTO_N ( (findex) )
    PROTO_T ( long findex )
{
    long i ;
    if ( open_label != 0 )
    {
	fprintf ( dg_file, "\t.stabn\t0x%x,0,%ld,%sL.%ld\n", N_LBRAC,
		  bracket_level, local_prefix, open_label ) ;
	open_label = 0 ;
    }
    i = next_lab () ;
    fprintf ( dg_file, "%sL.%ld:\n", local_prefix, i ) ;
    fprintf ( dg_file, "\t.stabn\t0x%x,0,%ld,%sL.%ld\n", N_RBRAC,
		  bracket_level, local_prefix, i ) ;
    bracket_level-- ;
    return ;
}


/*
    DEPTH COUNT FOR STAB TYPES
*/

static int max_depth = 64 ;
static int depth_now = 0 ;


/*
    OUTPUT A DIAGNOSTICS TYPE
*/

#define OUT_DT_SHAPE( dt )	out_dt_shape ( ( depth_now = 0, dt ) )

static void out_dt_shape
    PROTO_N ( (dt) )
    PROTO_T ( diag_type dt )
{
    if ( dt->been_outed ) {
	fprintf ( dg_file, "%d",(int) dt->been_outed ) ;
	last_type_sz = get_stab_size ( dt->been_outed ) ;
	return ;
    }

    /* SunOS as(1) rejects stab lines >2k so reduce size arbitrarily */
    if ( depth_now >= max_depth ) {
	fprintf ( dg_file, "%d", STAB_SLONG ) ;
	return ;
    }
    depth_now++ ;

    switch ( dt->key ) {

	case DIAG_TYPE_PTR : {
	    long non ;
	    diag_type pdt = dt->data.ptr.object ;
	    if ( pdt->key == DIAG_TYPE_VARIETY ) {
		long pn = out_sh_type ( f_integer ( pdt->data.var ) ) ;
		non = stab_ptrs [ pn ] ;
		if ( non == 0 ) {
		    non = next_typen () ;
		    stab_ptrs [ pn ] = non ;
		    fprintf ( dg_file, "%ld=*%ld", non, pn ) ;
		} else {
		    fprintf ( dg_file, "%ld", non ) ;
		}
	    } else {
		non = next_typen () ;
		fprintf ( dg_file, "%ld=*", non ) ;
		out_dt_shape ( dt->data.ptr.object ) ;
	    }
	    dt->been_outed = non ;
	    last_type_sz = 32 ;
	    set_stab_size ( non ) ;
	    break ;
	}

	case DIAG_TYPE_ARRAY : {
#if 0
	    long str = no ( dt->data.array.stride ) ;
#endif
	    long lwb = no ( dt->data.array.lower_b ) ;
	    long upb = no ( dt->data.array.upper_b ) ;
	    diag_type index_type = dt->data.array.index_type ;
	    diag_type element_type = dt->data.array.element_type ;
	    long non = next_typen () ;
	    dt->been_outed = non ;
	    fprintf ( dg_file, "%ld=ar", non ) ;
	    out_dt_shape ( index_type ) ;
	    fprintf ( dg_file, ";%ld;%ld;", lwb, upb ) ;
	    out_dt_shape ( element_type ) ;
	    last_type_sz *= ( upb - lwb + 1 ) ;
	    set_stab_size ( non ) ;
	    break ;
	}

	case DIAG_TYPE_STRUCT :
	case DIAG_TYPE_UNION : {
	    int i ;
	    char su ;
	    shape s ;
	    diag_field_list fields ;
	    long non = next_typen () ;
	    dt->been_outed = non ;

	    if ( dt->key == DIAG_TYPE_STRUCT ) {
		fields = dt->data.t_struct.fields ;
		s = dt->data.t_struct.tdf_shape ;
		su = 's';
	    } else {
		fields = dt->data.t_union.fields ;
		s = dt->data.t_union.tdf_shape;
		su = 'u' ;
	    }
	    fprintf ( dg_file, "%ld=%c%d", non, su, shape_size ( s ) / 8 ) ;

	    for ( i = fields->lastused - 1 ; i >= 0 ; i-- ) {
		diag_field sf =  ( fields->array ) [i] ;
		long offset = no ( sf->where );

		if ( depth_now >= max_depth ) return ;
		depth_now++ ;
		fprintf ( dg_file, "%s:", sf->field_name.ints.chars ) ;
		out_dt_shape ( sf->field_type ) ;
		fprintf ( dg_file, ",%ld,%ld;", offset, last_type_sz ) ;
	    }
	    fprintf ( dg_file, ";" ) ;
	    last_type_sz = shape_size ( s ) ;
	    set_stab_size ( non ) ;
	    break ;
	}

	case DIAG_TYPE_VARIETY : {
	    dt->been_outed = out_sh_type ( f_integer ( dt->data.var ) ) ;
	    fprintf ( dg_file, "%ld", dt->been_outed ) ;
	    break ;
	}

	case DIAG_TYPE_PROC: {
	    diag_type result_type = dt->data.proc.result_type ;
	    long non1 = next_typen () ;
	    long non2 = next_typen () ;
	    dt->been_outed = non1 ;
	    fprintf ( dg_file, "%ld=*%ld=f", non1, non2 ) ;
	    out_dt_shape ( result_type ) ;
	    last_type_sz = 32 ;
	    set_stab_size ( non1 ) ;
	    set_stab_size ( non2 ) ;
	    break ;
	}

	case DIAG_TYPE_LOC: {
	    /* +++ use qualifier which gives "const"/"volatile" */
	    out_dt_shape ( dt->data.loc.object ) ;
	    break ;
	}

	case DIAG_TYPE_FLOAT : {
	    dt->been_outed = out_sh_type ( f_floating ( dt->data.f_var ) ) ;
	    fprintf ( dg_file, "%ld", dt->been_outed ) ;
	    break ;
	}

	case DIAG_TYPE_NULL : {
	    fprintf ( dg_file, "%d", STAB_VOID ) ;
	    last_type_sz = 0 ;
	    break ;
	}

	case DIAG_TYPE_BITFIELD : {
	    long sz = dt->data.bitfield.no_of_bits.nat_val.small_nat ;
	    fprintf ( dg_file, "%d", STAB_SLONG ) ;
	    last_type_sz = sz ;
	    break ;
	}

	case DIAG_TYPE_ENUM : {
	    int i ;
	    enum_values_list enumvals = dt->data.t_enum.values;
	    long non = next_typen () ;
	    dt->been_outed = non ;
	    fprintf ( dg_file, "%ld=e", non ) ;
	    for ( i = enumvals->lastused - 1 ; i >= 0 ; i-- ) {
		enum_values ef =  ( enumvals->array ) [i] ;
		fprintf ( dg_file, "%s:%d,", ef->nme.ints.chars, no ( ef->val ) );
	    }
	    fprintf ( dg_file, ";" ) ;
	    last_type_sz = 32 ;
	    set_stab_size ( non ) ;
	    break ;
	}

	default : {
	    fprintf ( dg_file, "%d", STAB_VOID ) ;
	    last_type_sz = 0 ;
	    break ;
	}
    }
    return ;
}


/*
    OUTPUT DIAGNOSTICS FOR A GLOBAL VARIABLE
*/

void diag_val_begin
    PROTO_N ( (d, global, cname, pname) )
    PROTO_T ( diag_global * d X int global X int cname X char * pname )
{
  stabd ( find_file ( d->data.id.whence.file->file.ints.chars ),
	 ( long ) d->data.id.whence.line_no.nat_val.small_nat
	 , -N_DSLINE ) ;

  fprintf ( dg_file, "\t.stabs\t\"%s:%c",
	d->data.id.nme.ints.chars, (global ? 'G' : 'S'));
  OUT_DT_SHAPE ( d->data.id.new_type ) ;
  if (global)
    fprintf ( dg_file, "\",0x20,0,%d,0\n",
	d->data.id.whence.line_no.nat_val.small_nat);
  else {
    fprintf ( dg_file, "\",0x28,0,%d,",
	d->data.id.whence.line_no.nat_val.small_nat);
    if (cname == -1) {
      outs (pname);
    }
    else {
      outs(local_prefix);
      outn ((long)cname);
    };
    outnl ();
  };
  return ;
}

void diag_val_end
    PROTO_N ( (d) )
    PROTO_T ( diag_global * d )
{
  UNUSED(d);
  return;
}


/*
    OUTPUT DIAGNOSTICS FOR A PROCEDURE
*/

void diag_proc_begin
    PROTO_N ( (d, global, cname, pname) )
    PROTO_T ( diag_global * d X int global X int cname X char * pname )
{
  last_proc_pname = pname;
  last_proc_cname = cname;
  in_proc = 1;
  if (!d)
    return;

  stabd ( find_file ( d->data.id.whence.file->file.ints.chars ),
	 ( long ) d->data.id.whence.line_no.nat_val.small_nat
	 ,0) ;

  outs ("\t.stabs\t\"");
  outs (d->data.id.nme.ints.chars);
  if (global)
    outs (":F");
  else
    outs (":f");
  OUT_DT_SHAPE ( d->data.id.new_type->data.proc.result_type ) ;
  outs ("\",0x24,0,0,");
  out_procname ();
  outnl ();
  return ;
}

void diag_proc_end
    PROTO_N ( (d) )
    PROTO_T ( diag_global * d )
{
  UNUSED(d);
  in_proc = 0;
  return;
}



/*
    OUTPUT DIAGNOSTICS FOR A LOCAL VARIABLE
*/

static void stab_local
    PROTO_N ( (d, proc_no, acc) )
    PROTO_T ( diag_info * d X int proc_no X exp acc )
{
  int p, param_dec;
#ifdef NEWDIAGS
  long acc_type;
  if (name(acc) == name_tag) {
    acc_type = ptno(son(acc));
    if (no_frame && acc_type != reg_pl)
      return;
  }
  if (name(acc) != name_tag) {
    fprintf ( dg_file, "\t.stabs\t\"%s=i\",0x80,0,0,%d\n",
	d -> data.id_scope.nme.ints.chars, no(acc) );
  }
  else
  if (acc_type == reg_pl) {
    fprintf ( dg_file, "\t.stabs\t\"%s:r",
	d -> data.id_scope.nme.ints.chars );
    OUT_DT_SHAPE ( d -> data.id_scope.typ ) ;
    fprintf ( dg_file, "\",0x40,0,0,%d\n",
		reg_stabno [get_reg_no (no(son(acc)))]);
  }
  else
#endif
  {
    p = (no(acc) + no(son(acc))) / 8;
    param_dec = isparam(son(acc));

    fprintf ( dg_file, "\t.stabs\t\"%s:",
	d -> data.id_scope.nme.ints.chars );
    OUT_DT_SHAPE ( d -> data.id_scope.typ ) ;
    fprintf ( dg_file, "\",0x80,0,%d,",
	0 /* or line number? */ );
    if (param_dec)
      fprintf ( dg_file, "%d\n", p+8);
    else
      fprintf ( dg_file, "%d-%sdisp%d\n", p, local_prefix, proc_no);
  }
  return ;
}



/*
    DEAL WITH BASIC TYPES
*/

static void stab_types
    PROTO_Z ()
{
    total_type_sizes = NO_STABS ;
    typeno = NO_STABS ;
    type_sizes = ( long * ) xmalloc ( NO_STABS * sizeof ( long ) ) ;
    fputs ( "\t.stabs\t\"int:t1=r1;-2147483648;2147483647;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"short int:t2=r1;-32768;32767;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"short unsigned int:t3=r1;0;65535;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"char:t4=r4;0;127;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"signed char:t5=r1;-128;127;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"unsigned char:t6=r1;0;255;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"long int:t7=r1;-2147483648;2147483647;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"unsigned int:t8=r1;0;-1;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"long unsigned int:t9=r1;0;-1;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"float:t10=r1;4;0;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"double:t11=r1;8;0;\",0x80,0,0,0\n",
	    dg_file ) ;
    fprintf ( dg_file, "\t.stabs\t\"long double:t12=r1;%d;0;\",0x80,0,0,0\n",
	      DOUBLE_SZ / 8 ) ;
    fputs ( "\t.stabs\t\"void:t13=13\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"long long int:t14=r1;", dg_file ) ;
    fputs ( "01000000000000000000000;0777777777777777777777;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"unsigned long long int:t15=r1;", dg_file ) ;
    fputs ( "0000000000000;01777777777777777777777;\",0x80,0,0,0\n",
	    dg_file ) ;
    type_sizes [0] = 0 ;
    type_sizes [1] = 32 ;
    type_sizes [2] = 16 ;
    type_sizes [3] = 16 ;
    type_sizes [4] = 8 ;
    type_sizes [5] = 8 ;
    type_sizes [6] = 8 ;
    type_sizes [7] = 32 ;
    type_sizes [8] = 32 ;
    type_sizes [9] = 32 ;
    type_sizes [10] = 32 ;
    type_sizes [11] = 64 ;
    type_sizes [12] = DOUBLE_SZ ;
    type_sizes [13] = 0 ;
    type_sizes [14] = 64 ;
    type_sizes [15] = 64 ;
    return ;
}


/*
    DEAL WITH STRUCTURE, UNION AND ENUM TAGS
*/

void stab_tagdefs
    PROTO_Z ()
{
    diag_tagdef **di = unit_ind_diagtags ;
    int i, n = unit_no_of_diagtags, istag ;

    for ( i = 0 ; i < n ; i++ ) {
	diag_type d = di [i]->d_type ;
	istag = 1;

	switch ( d->key ) {

	    case DIAG_TYPE_STRUCT : {
		char *nme = d->data.t_struct.nme.ints.chars ;
		if ( nme && *nme ) {
		    fprintf ( dg_file, "\t.stabs\t\"%s:", nme ) ;
		} else {
		    static int s_count = 0 ;
		    fprintf ( dg_file, "\t.stabs\t\"_struct%d:", s_count++ ) ;
		}
		break ;
	    }
	    case DIAG_TYPE_UNION : {
		char *nme = d->data.t_union.nme.ints.chars ;
		if ( nme && *nme ) {
		    fprintf ( dg_file, "\t.stabs\t\"%s:", nme ) ;
		} else {
		    static int u_count = 0 ;
		    fprintf ( dg_file, "\t.stabs\t\"_union%d:", u_count++ ) ;
		}
		break ;
	    }
	    case DIAG_TYPE_ENUM : {
		char *nme = d->data.t_enum.nme.ints.chars ;
		if ( nme && *nme ) {
		    fprintf ( dg_file, "\t.stabs\t\"%s:", nme ) ;
		} else {
		    static int e_count = 0 ;
		    fprintf ( dg_file, "\t.stabs\t\"_enum%d:", e_count++ ) ;
		}
		break ;
	    }
	    default: {
		istag = 0 ;
		break ;
	    }
	}
	if (istag) {
	    if ( d->been_outed && 0) {
		fprintf ( dg_file, "%d", (int)d->been_outed ) ;
	    } else {
		fprintf ( dg_file, "T" ) ;
		OUT_DT_SHAPE ( d ) ;
	    }
	    fprintf ( dg_file, "\",0x80,0,0,0\n" ) ;
	}
    }
    return ;
}


/*
    DEAL WITH TYPEDEFS
*/

void stab_typedefs
    PROTO_Z ()
{
    diag_descriptor *di = unit_diagvar_tab.array ;
    int i, n = unit_diagvar_tab.lastused ;
    for ( i = 0 ; i < n ; i++ ) {
	if ( di [i].key == DIAG_TYPEDEF_KEY ) {
	    long non = next_typen () ;
	    fprintf ( dg_file, "\t.stabs\t\"%s:t%ld=",
		      di [i].data.typ.nme.ints.chars, non ) ;
	    OUT_DT_SHAPE ( di [i].data.typ.new_type ) ;
	    fprintf ( dg_file, "\",0x80,0,0,0\n" ) ;
	}
    }
    return ;
}
