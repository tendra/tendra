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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/xdb_output.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: xdb_output.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:02  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:23  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:02  john
 *
 * Revision 1.2  1996/07/05  14:36:22  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:29  ra
 * Added missing files.
 * 
 * Revision 1.1  93/02/22  17:17:27  17:17:27  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef XDB_OUTPUT_INCLUDED
#define XDB_OUTPUT_INCLUDED


/*
    TYPE REPRENTING DIAGNOSTIC DIRECTIVES
*/

typedef struct {
    int instr ;
    long old_size ;
    long new_size ;
} diag_directive ;

extern diag_directive dd [] ;


/*
    INDEX TO ARRAY OF DIAGNOSTIC DIRECTIVES

    These macros correspond to the entries in the table above.
*/

#define  xdb_array		0
#define  xdb_begin		1
#define  xdb_const		2
#define  xdb_dvar		3
#define  xdb_end		4
#define  xdb_entry		5
#define  xdb_enum		6
#define  xdb_field		7
#define  xdb_file		8
#define  xdb_fparam		9
#define  xdb_function		10
#define  xdb_functype		11
#define  xdb_import		12
#define  xdb_label		13
#define  xdb_memenum		14
#define  xdb_module		15
#define  xdb_pointer		16
#define  xdb_set		17
#define  xdb_srcfile		18
#define  xdb_struct		19
#define  xdb_subrange		20
#define  xdb_svar		21
#define  xdb_tagdef		22
#define  xdb_typedef		23
#define  xdb_union		24
#define  xdb_variant		25


/*
    DIAGNOSTIC FORMS SUPPORTED
*/

#define  DIAG_XDB_OLD		0
#define  DIAG_XDB_NEW		1
#define  DIAG_STAB		2
#define  DIAG_UNKNOWN		3


extern bool diag_format ;
extern long crt_diag_proc_lab ;

extern void init_diag PROTO_S ( ( void ) ) ;
extern void copy_diag PROTO_S ( ( void ) ) ;
extern void slt_exit PROTO_S ( ( void ) ) ;
extern void dnt_begin PROTO_S ( ( void ) ) ;
extern int dnt_end PROTO_S ( ( void ) ) ;
extern void diag_string PROTO_S ( ( FILE *, char * ) ) ;
extern void diag_source PROTO_S ( ( char *, long, int ) ) ;
extern void diag_source_file PROTO_S ( ( char *, long ) ) ;
extern void diag_globl_variable PROTO_S ( ( diag_type, char *, int, char *, int ) ) ;
extern void diag_local_variable PROTO_S ( ( diag_type, char *, long ) ) ;
extern void diag_type_defn PROTO_S ( ( char *, diag_type ) ) ;
extern void diag_proc_main PROTO_S ( ( diag_type, exp, char *, int, char * ) ) ;

#endif
