/*
    		 Crown Copyright (c) 1997, 1998
    
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


#ifndef VERSION_INCLUDED
#define VERSION_INCLUDED


/*
    VERSION NUMBERS

    These macros give the version numbers for the various interfaces
    supported by the program and the overall version number for the
    program itself.  Note that the C and C++ version numbers are the
    values of the __STDC_VERSION__ and __cplusplus macros, respectively.
*/

#ifndef PROG_VERSION
#define PROG_VERSION		"1.8.2"
#endif

#ifndef PROG_DATE
#define PROG_DATE		"Mar 16 1998"
#endif

#ifndef CPP_VERSION
#define CPP_VERSION		"199611L"
#endif

#ifndef C_VERSION
#define C_VERSION		"1"
#endif

#ifndef ISOC_VERSION
#define ISOC_VERSION		"199409L"
#endif

#ifndef TDF_VERSION
#define TDF_VERSION		401
#endif

#ifndef TDF_OUTPUT
#define TDF_OUTPUT		1
#endif

#ifndef DIAG_VERSION
#define DIAG_VERSION		2
#endif

#ifndef SPEC_VERSION
#define SPEC_VERSION		100
#endif

#ifndef DUMP_VERSION
#define DUMP_VERSION		101
#endif


#endif
