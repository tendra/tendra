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


#ifndef OPTIONS_INCLUDED
#define OPTIONS_INCLUDED


/*
    TYPE REPRESENTING AN OPTION

    An option consists of an input pattern, in, an output command, out,
    and some explanitory text, explain.
*/

typedef struct {
    char *in ;
    char *out ;
    char *explain ;
} optmap ;


/*
    TYPE REPRESENTING AN OPTION ACTION

    The output commands of an optmap are stored as an args_out, which is
    a simple array of strings.
*/

#define max_var		100

typedef struct {
    int argc ;
    char *argv [ max_var ] ;
} args_out ;


/*
    TABLES OF OPTIONS

    These tables give the option mappings for the command-line options
    and the environment options.
*/

extern optmap main_optmap [] ;
extern optmap environ_optmap [] ;


/*
    PROCEDURE DECLARATIONS

    These routines are concerned with processing command-line options
    and input files.
*/

extern void process_options PROTO_S ( ( list *, optmap * ) ) ;


/*
    THE LIST OF ALL INPUT FILES

    All the input files are formed into this list.
*/

extern filename *input_files ;


#endif
