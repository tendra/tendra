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


#ifndef OSSG_STD_INCLUDED
#define OSSG_STD_INCLUDED


/*
    STANDARD C HEADER

    These pragmas describe the extra checks to be applied to the program
    by the TenDRA C compiler.  They encapsulate the coding standard to
    be applied.
*/

#ifdef __TenDRA__

#pragma TenDRA begin

#pragma TenDRA complete struct/union analysis warning
#pragma TenDRA conversion analysis (int-int implicit) warning
#pragma TenDRA conversion analysis (int-pointer) warning
#pragma TenDRA conversion analysis (pointer-pointer) warning
#pragma TenDRA discard analysis warning
#pragma TenDRA implicit function declaration off
#pragma TenDRA incompatible interface declaration disallow
#pragma TenDRA incompatible void return disallow
#pragma TenDRA variable analysis warning
#pragma TenDRA weak prototype analysis on

#pragma TenDRA linkage resolution : (internal) warning
#pragma TenDRA no external declaration disallow
#pragma TenDRA initialization of struct/union (auto) disallow
#pragma TenDRA text after directive disallow
#pragma TenDRA unknown escape disallow
#pragma TenDRA unknown pragma warning

#ifndef OLD_PRODUCER
#pragma TenDRA fall into case warning
#pragma TenDRA unreachable code warning
#endif

#endif


#endif
