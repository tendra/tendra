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


/* 80x86/messages_8.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: messages_8.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/14  13:54:02  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.2  1995/01/30  12:56:35  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:37:52  jmf
 * Initial revision
 *
**********************************************************************/

#ifndef messages_8_key
#define messages_8_key 1


#define NO_SETCC "no setcc"
#define NO_BITPTRS "no bit pointers yet"
#define WRONG_REGSIZE "wrong reg size"
#define BADOP "bad operation"
#define SEEK_FAILURE "internal seek failure"
#define BAD_FSTACK "bad floating point stack"
#define FSTACK_UNSET "floating point stack level not set"
#define BAD_TESTNO "bad test number"
#define BAD_MOVE_SIZE "illegal move size"
#define BAD_BIT_OPND "illegal bit opnd"
#define BAD_FLOP "illegal floating point operation"
#define BAD_REGISTER "illegal register"
#define BAD_OPND "illegal operand"
#define BAD_VAL "illegal val const"
#define CPD_ORDER "compound constants out of order"
#define BAD_CHVAR "illegal constant expression"
#define BAD_CONST "illegal constant expression"
#define BAD_CLOSE "cannot close file"
#define BAD_OUTPUT "cannot output"
#define BAD_FLAG "illegal flag"
#define BAD_COMMAND1 "install: needs both an input and an output file"
#define BAD_COMMAND2 "install: input and output cannot be equal"
#define CANT_OPEN "install: cant open output file"
#define CANT_READ "install: cant read input file"
#define STRUCT_RETURN "cant apply return to struct"
#define STRUCT_RES "cant get struct result from procedure"
#define BAD_POSTLUDE "illegal postlude"

#endif
