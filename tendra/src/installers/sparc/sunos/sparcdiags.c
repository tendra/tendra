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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/sunos/sparcdiags.c,v 1.1.1.1 1998/01/17 15:55:56 release Exp $
--------------------------------------------------------------------------
$Log: sparcdiags.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/04/04  15:23:59  pwe
 * tidy re old DWARF interface
 *
 * Revision 1.2  1997/04/01  17:18:04  pwe
 * diagnose pl_tests
 *
 * Revision 1.1  1997/03/24  17:10:19  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.11  1997/02/18  11:48:22  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.10  1996/09/10  14:36:55  pwe
 * fix diags - nested scope, param struct and leaf return
 *
 * Revision 1.9  1996/09/09  08:39:55  pwe
 * correct stabs enums
 *
 * Revision 1.8  1995/12/15  10:27:23  john
 * Fixed error in previous fix
 *
 * Revision 1.7  1995/11/23  15:21:31  john
 * Fix for diagnostics (nested structures)
 *
 * Revision 1.6  1995/07/03  09:30:13  john
 * Fixed error
 *
 * Revision 1.5  1995/06/29  08:20:22  john
 * Reformatting
 *
 * Revision 1.4  1995/06/27  08:47:38  john
 * Some reformatting
 *
 * Revision 1.3  1995/04/20  08:06:36  john
 * Minor change
 *
 * Revision 1.2  1995/03/27  12:50:40  john
 * Fix for c-style varargs handling
 *
 * Revision 1.1.1.1  1995/03/13  10:18:56  john
 * Entered into CVS
 *
 * Revision 1.7  1995/01/11  16:40:35  john
 * Fixed bug in diagnostics (for change request CR95_40)
 *
 * Revision 1.6  1995/01/11  09:59:32  john
 * Fixed bug in diagnostics (for change request CR94_224)
 *
 * Revision 1.5  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.4  1994/07/04  08:29:06  djch
 * added extra parameter to stabd (section number). -ve values used to control
 * not putting out stabd (sometimes) in solaris; line #s go in the stabs.
 * added assert(0) to catch uninitialized items.
 *
 * Revision 1.3  1994/06/22  09:48:33  djch
 * Changes for solaris - line #s in functions are relative to start of fns,
 * global decls have line # in the stabs, and no stabn, and local labels are .LL,
 * not LL
 *
 * Revision 1.2  1994/05/13  13:08:39  djch
 * Incorporates improvements from expt version
 * changed format strings to remove longs..
 *
 * Revision 1.1  1994/05/03  14:49:53  djch
 * Initial revision
 *
 * Revision 1.6  93/09/27  14:55:15  14:55:15  ra (Robert Andrews)
 * Only whitespace.
 * 
 * Revision 1.5  93/08/27  11:37:55  11:37:55  ra (Robert Andrews)
 * A couple of lint-like changes.
 * 
 * Revision 1.4  93/08/13  14:45:51  14:45:51  ra (Robert Andrews)
 * Allow the stabs for long double to vary depending on DOUBLE_SZ.
 * 
 * Revision 1.3  93/07/05  18:26:29  18:26:29  ra (Robert Andrews)
 * A couple of minor corrections.  Introduced stab_ptrs to avoid duplication
 * of basic pointer types.
 * 
 * Revision 1.2  93/06/29  14:32:54  14:32:54  ra (Robert Andrews)
 * Fairly major rewrite and reformat.  There were a number of errors which
 * meant that the diagnostics were not previously working.
 * 
 * Revision 1.1  93/06/24  14:59:22  14:59:22  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "addrtypes.h"
#include "exptypes.h"
#include "shapemacs.h"
#include "expmacs.h"
#include "codetypes.h"
#include "installtypes.h"
#include "toktypes.h"
#include "exp.h"
#include "exptypes.h"
#include "proctypes.h"
#include "procrec.h"
#include "tags.h"
#include "bitsmacs.h"
#include "diagtypes.h"
#include "xalloc.h"
#include "diag_fns.h"
#include "locate.h"
#include "diagglob.h"
#include "mark_scope.h"
#include "xalloc.h"
#include "comment.h"
#include "myassert.h"
#include "translat.h"
#include "machine.h"
#include "szs_als.h"
#include "install_fns.h"
#include "installglob.h"
#include "externs.h"
#include "out.h"
#include "sparcdiags.h"
extern bool last_param PROTO_S ( ( exp ) ) ;


/*
  FORWARD DECLARATIONS
*/

static long stab_scope_open PROTO_S ( ( long ) ) ;
static void stab_scope_close PROTO_S ( ( long ) ) ;
static void ready_scope PROTO_S ( ( void ) );


	/* label number sequence independent from text code */
static int diag_lab_no = 0;

static int next_d_lab
    PROTO_Z ()
{
  return ++diag_lab_no;
}


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
#define NO_STABS	14


/*
  BASIC POINTERS
*/

static long stab_ptrs [ NO_STABS ] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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
    type_sizes = ( long * ) xrealloc ( type_sizes, m * sizeof ( long ) ) ;
    for ( i = n ; i < m ; i++ ) type_sizes [i] = 0 ;
    total_type_sizes = m ;
  }
  return ( typeno++ ) ;
}


/*
    ARRAY OF FILE DESCRIPTORS
*/

static filename *fds = null ;
static int szfds = 0 ;
static int nofds = 0 ;


/*
  ADD A NEW FILE TO THE ARRAY OF FILE DESCRIPTORS
*/

void stab_collect_files 
    PROTO_N ( ( f ) )
    PROTO_T ( filename f )
{
  if ( fds == null ) {
    szfds += 10 ;
    fds = ( filename * ) xmalloc ( szfds * sizeof ( filename ) ) ;
  } 
  else if ( nofds >= szfds ) {
    szfds += 10 ;
    fds = ( filename * ) xrealloc ( fds, szfds * sizeof ( filename ) ) ;
  }
  fds [ nofds++ ] = f ;
  return ;
}


/*
  FIND THE FILE DESCRIPTOR CORRESPONDING TO A FILE NAME
*/

static long find_file 
    PROTO_N ( ( f ) )
    PROTO_T ( char * f )
{
  long i ;
  for ( i = 0 ; i < nofds ; i++ ) {
    if ( strcmp ( f, fds [i]->file.ints.chars ) == 0 ) return ( i ) ;
  }
  return ( 0 ) ;
}



/*
  OUTPUT A FILE POSITION CONSTRUCT
*/

#define N_SLINE 0x44
#define N_DSLINE 0x46
#define N_BSLINE 0x48

void stabd 
    PROTO_N ( ( findex, lno, seg ) )
    PROTO_T ( long findex X long lno X int seg )
{
  long i ;
  if ( findex == currentfile && lno == currentlno ) return ;
  stab_file ( findex, 1 ) ;
  
  if (seg != 0){		/* 0 suppresses always */
      
    if (seg > 0)	/* -ve line nos are put out in the stabs */
      {
	i = next_d_lab () ;
	fprintf ( dg_file, "\t.stabn\t0x%x,0,%ld,LL.%ld\n",seg, lno, i ) ;
	fprintf ( dg_file, "LL.%ld:\n", i ) ;
      }
  }
  currentlno = lno ;
  return ;
}


#ifdef NEWDIAGS
/*
    OUTPUT DIAGNOSTICS SURROUNDING CODE
*/

void code_diag_info (d, proc_no, mcode, args)
diag_info * d;
int proc_no;
void (*mcode)();
void * args;
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
	ready_scope () ;
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
	  fail("not hold_tag");
	acc = son(acc);
	if (name(acc) == cont_tag && name(son(acc)) == name_tag && isvar(son(son(acc))))
	  acc = son(acc);
	if ( name(acc) == name_tag && !isdiscarded(acc) && !isglob(son(acc)) ) {
	  stab_local ( d->data.id_scope.nme.ints.chars, d->data.id_scope.typ,
	       acc, 0, currentfile ) ;

	  if ( last_param ( son ( acc ) ) ) {
	    stabd ( currentfile, ( long ) ( currentlno + 1 ),N_SLINE) ;
	  }
	}
	else if ( name(acc) == val_tag ) {
	  ; /* should be able to do something with val_tag */
	}
	code_diag_info (d->more, proc_no, mcode, args);
    }
  };
  return;
}


#else

/*
  OUTPUT INITIAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void stab_begin 
    PROTO_N ( ( d, proc_no, e ) )
    PROTO_T ( diag_info * d X int proc_no X exp e )
{
  exp x ;

  if ( d->key == DIAG_INFO_SOURCE ) {
    sourcemark *s = &d->data.source.beg ;
    long f = find_file ( s->file->file.ints.chars ) ;
    ready_scope () ;
    stabd ( f, ( long ) s->line_no.nat_val.small_nat ,N_SLINE) ;
    return ;
  }
  
  if ( d->key != DIAG_INFO_ID ) {
    /* not implemented */
    return ;
  }
  
  x = d->data.id_scope.access ;
  /* MIPS */
  if ( isglob ( son ( x ) ) || no ( son ( x ) ) == 1 ) return;
  
  mark_scope ( e ) ;
  if ( props ( e ) & 0x80 ) {
    ( void ) stab_scope_open ( currentfile ) ;
    stabd ( currentfile, ( long ) ( currentlno + 1 ), N_SLINE ) ;
  }
  
  stab_local ( d->data.id_scope.nme.ints.chars, d->data.id_scope.typ,
	       x, 0, currentfile ) ;

  if ( last_param ( son ( x ) ) ) {
    stabd ( currentfile, ( long ) ( currentlno + 1 ),N_SLINE) ;
  }
  return ;
}


/*
  OUTPUT FINAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void stab_end 
    PROTO_N ( ( d, e ) )
    PROTO_T ( diag_info * d X exp e )
{
  if ( d->key == DIAG_INFO_SOURCE ) {
    sourcemark *s = &d->data.source.end ;
    long f = find_file ( s->file->file.ints.chars ) ;
    long lno = s->line_no.nat_val.small_nat ;
    stabd (f,(long)lno,N_SLINE);
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

void init_stab 
    PROTO_Z ()
{
  dg_file_name = tmpnam ( NULL ) ;
  dg_file = fopen ( dg_file_name, "w" ) ;
  if ( dg_file == NULL ) {
    fail ( "Can't open temporary diagnostics file" ) ;
    exit ( EXIT_FAILURE ) ;
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
  int i, j = 0 ;
  for ( i = 0 ; i < nofds ; i++ ) {
    char *s = fds [i]->file.ints.chars ;
    int n = ( int ) strlen ( s ) ;
    if ( n && s [ n - 1 ] != 'h' ) j = i ;
  }
  fclose ( dg_file ) ;
  dg_file = as_file ;
  stab_file ( ( long ) j, 0 ) ;
  f = fopen ( dg_file_name, "r" ) ;
  if ( f == NULL ) {
    fail ( "Can't open temporary diagnostics file" ) ;
    exit ( EXIT_FAILURE ) ;
  }
  while ( c = fgetc ( f ), c != EOF ) outc ( c ) ;
  fclose ( f ) ;
  remove ( dg_file_name ) ;
  return ;
}


/*
  FIND THE STAB OF A SIMPLE SHAPE
*/

static long out_sh_type 
    PROTO_N ( ( s ) )
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
    case shrealhd : return ( STAB_FLOAT ) ;
    case realhd : return ( STAB_DBL ) ;
    case doublehd : return ( STAB_LDBL ) ;
  }
  return ( STAB_VOID ) ;
}


/*
  OUTPUT DIAGNOSTICS DIRECTIVE FOR A FILE
*/

void stab_file 
    PROTO_N ( ( findex, internal ) )
    PROTO_T ( long findex X bool internal )
{
  static long i = 0 ;
  
  if ( findex == currentfile || findex < 0 || findex >= szfds ) {
    return ;
  }

  if ( !internal ) {
    /* source file */
    i = next_d_lab () ;
    fprintf ( dg_file, "\t.stabs\t\"%s\",0x64,0,0,LL.%ld\n",
	      fds [ findex ]->file.ints.chars, i ) ;
    fprintf ( dg_file, "LL.%ld:\n", i ) ;
  } 
  else {
    /* included file */
    fprintf ( dg_file, "\t.stabs\t\"%s\",0x84,0,0,LL.%ld\n",
	      fds [ findex ]->file.ints.chars, i ) ;
    }
    currentfile = findex ;
    return ;
}


/*
  DIAGNOSTIC SCOPES
*/

static long open_label = 0 ;
static long bracket_level = 1 ;

static void ready_scope 
    PROTO_Z ()
{
  if ( open_label != 0 ) {
    fprintf ( dg_file, "\t.stabn\t0xc0,0,%ld,LL.%ld\n",
	      bracket_level, open_label ) ;
    open_label = 0 ;
  }
}


/*
  START OF A DIAGNOSTICS SCOPE
*/

static long stab_scope_open 
    PROTO_N ( ( findex ) )
    PROTO_T ( long findex )
{
  long i ;
  stab_file ( findex, 1 ) ;
  i = next_d_lab () ;
  ready_scope ();
  fprintf ( dg_file, "LL.%ld:\n", i ) ;
  open_label = i ;
  bracket_level++ ;
  return ( i ) ;
}


/*
  END OF A DIAGNOSTICS SCOPE
*/

static void stab_scope_close 
    PROTO_N ( ( findex ) )
    PROTO_T ( long findex )
{
  long i ;
  bracket_level-- ;
  if ( open_label != 0 ) {
    ready_scope ();
    open_label = 0 ;
  }
  i = next_d_lab () ;
  fprintf ( dg_file, "\t.stabn\t0xe0,0,%ld,LL.%ld\n",
	      bracket_level, i ) ;
  fprintf ( dg_file, "LL.%ld:\n", i ) ;
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
    PROTO_N ( ( dt ) )
    PROTO_T ( diag_type dt )
{
  if ( dt->been_outed ) {
    fprintf ( dg_file, "%d",(int) dt->been_outed ) ;
    last_type_sz = get_stab_size ( dt->been_outed ) ;
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
	} 
	else {
	  fprintf ( dg_file, "%ld", non ) ;
	}
      } 
      else {
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
      long lwb = no ( dt->data.array.lower_b ) ;
      long upb = no ( dt->data.array.upper_b ) ;
      diag_type index_type = dt->data.array.index_type ;
      diag_type element_type = dt->data.array.element_type ;
      long non = next_typen () ;
      dt->been_outed = non ;
      fprintf ( dg_file, "%ld=", non ) ;
      fprintf ( dg_file, "ar" ) ;
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
      } 
      else {
	fields = dt->data.t_union.fields ;
	s = dt->data.t_union.tdf_shape;
	su = 'u' ;
      }
      fprintf ( dg_file, "%ld=%c%d", non, su, shape_size ( s ) / 8 ) ;

      for ( i = fields->lastused - 1 ; i >= 0 ; i-- ) {
	diag_field sf =  ( fields->array ) [i] ;
	long offset = no ( sf->where );
	
/*	if ( depth_now >= max_depth ) return ;*/
	if(depth_now >= max_depth){
	  depth_now = 0;
	  fprintf (dg_file, "\\\\\",0x80,0,%d,%d\n",0,0 ) ;
	  fprintf(dg_file,"\t.stabs\t\"");
	}
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
  
    case DIAG_TYPE_PROC : {
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
  
    case DIAG_TYPE_LOC : {
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

void stab_global 
    PROTO_N ( ( dd, global, id, ext ) )
    PROTO_T ( diag_descriptor * dd X exp global X char * id X bool ext )
{
  if ( dd == NULL ) return ;
  
  stabd ( find_file ( dd->data.id.whence.file->file.ints.chars ),
	 ( long ) dd->data.id.whence.line_no.nat_val.small_nat
	 , -N_DSLINE ) ;

  fprintf ( dg_file, "\t.stabs\t\"%s:%c", dd->data.id.nme.ints.chars,
	   ( ext ? 'G' : 'S' ) ) ;
  OUT_DT_SHAPE ( dd->data.id.new_type ) ;
  fprintf ( dg_file, "\",%#x,0,%d,%s\n", ( ext ? 0x24 : ((no(global)!=0)?0x26:0x28) ),
	   dd->data.id.whence.line_no.nat_val.small_nat /*0*/,
	   id
	   ) ;
  return ;
}


/*
  OUTPUT DIAGNOSTICS FOR A PROCEDURE
*/

void stab_proc 
    PROTO_N ( ( dd, proc, id, ext ) )
    PROTO_T ( diag_descriptor * dd X exp proc X char * id X bool ext )
{
  if ( dd == NULL ) return ;
  
  stabd ( find_file ( dd->data.id.whence.file->file.ints.chars ),
	 ( long ) dd->data.id.whence.line_no.nat_val.small_nat 
	 ,0) ;

  fprintf ( dg_file, "\t.stabs\t\"%s:%c",
	   dd->data.id.nme.ints.chars, ( ext ? 'F' : 'f' ) ) ;
  OUT_DT_SHAPE ( dd->data.id.new_type->data.proc.result_type ) ;
  fprintf ( dg_file, "\",0x24,0,%d,%s\n", 0, id ) ;
  return ;
}


/*
  OUTPUT DIAGNOSTICS FOR A LOCAL VARIABLE
*/

void stab_local
    PROTO_N ( ( nm, dt, ldid, disp, findex ) )
    PROTO_T ( char *nm X diag_type dt X exp ldid X long disp X long findex )
{
  exp id = son ( ldid ) ;

  if (name (id) == ident_tag && ((props (id) & defer_bit) == 0))
    disp += boff ( id ).offset ;	/* is this condition right ? */
  again :
    if ( name ( id ) == ident_tag ) {
      if ( ( props ( id ) & defer_bit ) == 0 ) {
	/* +++ add assembler comment to say which reg is being used */
	if ( isparam ( id ) ) {
	  fprintf ( dg_file, "\t.stabs\t\"%s:p", nm ) ;
	  OUT_DT_SHAPE ( dt ) ;
	  fprintf ( dg_file, "\",0xa0,0,%d,%ld\n",
		    0,
		    disp ) ;
	  if(disp <= 88) { /* register useage comment */
	    fprintf(dg_file, "\t.stabs\t\"%s:r",nm);
	    OUT_DT_SHAPE(dt);
	    fprintf(dg_file,"\",0x40,0,%d,%ld\n",0,24+ ((disp-68)/4));
	  }
	  return ;
	} 
	else {
	  fprintf ( dg_file, "\t.stabs\t\"%s:", nm ) ;
	  OUT_DT_SHAPE ( dt ) ;
	  fprintf ( dg_file, "\",0x80,0,%d,%ld\n",
		    0,
		    disp ) ;
	  return ;
	}
      } 
      else {
	exp sn = son ( id ) ;
	long d = disp ;

	while ( sn != nilexp ) {
	  switch ( name ( sn ) ) {
	    case name_tag : {
	      disp = d + no ( sn ) ;
	      id = son ( sn ) ;
	      if ( isvar ( id ) ) dt = dt->data.ptr.object ;
	      goto again ;
	    }
	    case reff_tag : {
	      d += no ( sn ) ;
	      sn = son ( sn ) ;
	      break ;
	    }
	    case cont_tag : {
	      sn = son ( sn ) ;
	      break ;
	    }
	    default : {
	      return ;
	    }
	  }
	}
      }
    }
  return ;
}


/*
  DEAL WITH BASIC TYPES
*/

void stab_types 
    PROTO_Z ()
{
  total_type_sizes = NO_STABS ;
  typeno = NO_STABS ;
  type_sizes = ( long * ) xmalloc ( NO_STABS * sizeof ( long ) ) ;
  fputs ( "\t.stabs\t\"int:t1=r1;-2147483648;2147483647;\",0x80,0,0,0\n", dg_file ) ;
  fputs ( "\t.stabs\t\"short int:t2=r1;-32768;32767;\",0x80,0,0,0\n",
	    dg_file ) ;
  fputs ( "\t.stabs\t\"short unsigned int:t3=r1;0;65535;\",0x80,0,0,0\n", dg_file ) ;
  fputs ( "\t.stabs\t\"char:t4=r4;0;127;\",0x80,0,0,0\n", dg_file ) ;
  fputs ( "\t.stabs\t\"signed char:t5=r1;-128;127;\",0x80,0,0,0\n",
	  dg_file ) ;
  fputs ( "\t.stabs\t\"unsigned char:t6=r1;0;255;\",0x80,0,0,0\n",
	  dg_file ) ;
  fputs ( "\t.stabs\t\"long int:t7=r1;-2147483648;2147483647;\",0x80,0,0,0\n", dg_file ) ;
    fputs ( "\t.stabs\t\"unsigned int:t8=r1;0;-1;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"long unsigned int:t9=r1;0;-1;\",0x80,0,0,0\n",
	    dg_file ) ;
    fputs ( "\t.stabs\t\"float:t10=r1;4;0;\",0x80,0,0,0\n", dg_file ) ;
    fputs ( "\t.stabs\t\"double:t11=r1;8;0;\",0x80,0,0,0\n", dg_file ) ;
    fprintf ( dg_file, "\t.stabs\t\"long double:t12=r1;%ld;0;\",0x80,0,0,0\n",
	      DOUBLE_SZ / 8 ) ;
    fputs ( "\t.stabs\t\"void:t13=13\",0x80,0,0,0\n", dg_file ) ;
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
