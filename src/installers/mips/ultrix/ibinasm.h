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
$Date: 1998/01/17 15:56:04 $
$Revision: 1.1.1.1 $
$Log: ibinasm.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:04  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/10/17  16:36:35  currie
 * Nugatory
 *
 * Revision 1.1  1995/04/13  09:33:41  currie
 * Initial revision
 *
***********************************************************************/
/****************************************************************** 
               ibinasm.h
   Structures and constants for outputting binary assembly format
******************************************************************/


#ifndef IBINASM
#define IBINASM

typedef unsigned int  asmopcode;
typedef unsigned int  asmformat;
typedef unsigned int  asmreg;
typedef int asmint;
typedef int asmsym;

#define zero 0
#define float_register 32
#define xnoreg 64

#define icprestore 15 
	/* this is not used - here to retain same new_code.c for BIGEND */

#define ilabel		 0
#define isym		 1
#define iglobal		 2
#define iabort		 3
#define ialign		 4
#define iascii		 5
#define iasciiz		 6
#define ibyte		 7
#define icomm		 8
#define ilcomm		 9
#define idata		10
#define idouble		11
#define ifile		12
#define ifloat		13
#define ihalf		14
#define iline		15
#define idead		16
#define inop		17
#define ireserved1	18
#define ireserved2	19
#define ispace		20
#define itext		21
#define iword		22
#define iocode		23
#define iend		24
#define isdata		25
#define irdata		26
#define ient		27
#define iloc		28
#define ibgnb		29
#define iendb		30
#define iasm0		31
#define iset		32
#define iorg		33
#define irep		34
#define iendrep		35
#define ilab		36
#define ivreg		37
#define imask		38
#define ifmask		39
#define ierr		40
#define iglobabs	41
#define iverstamp	42
#define iframe		43
#define iextended	44
#define iextern		45
#define iaent		46
#define ioption		47
#define inoalias	48
#define ialias		49

#define igpword 	50
	/* unused except for PIC_code */

#define formrob	 0
#define formra	 1
#define formri	 2
#define formrrr	 3
#define formrri	 4
#define formrr	 5
#define forma	 6
#define formr	 7
#define formrrl	 8
#define formrl	 9
#define forml	10
#define forrr	11
#define formril	12
#define formi	13

#define set_undefined	 0
#define set_reorder	 1
#define set_noreorder	 2
#define set_macro	 3
#define set_nomacro	 4
#define set_at		 5
#define set_noat	 6
#define set_move	 7
#define set_nomove	 8
#define set_bopt	 9
#define set_nobopt	10
#define set_volatile	11
#define set_novolatile	12

#define o_undefined	 0
#define o_optimize	 1
#define o_other		 2

#define opt_none	 0
#define opt_int		 1
#define opt_float	 2
#define opt_string	 3

#define binasm_record_length 16

typedef union {
  char  data[binasm_record_length];
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
  }       common;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
    unsigned  lexlev;
  }       ent;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
              asmint frameoffset;
#ifndef V210
          asmreg framereg:           7;
          asmreg pcreg:           7;
#else
	  asmreg framereg:	8;
	  asmreg pcreg:		8;
#endif	  
	  
  }       frame;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
    unsigned  regmask;
              asmint regoffset;
  }       mask;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
    int   majornumber;
    int   minornumber;
  }       verstamp;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
    unsigned  filenumber;
    unsigned  linenumber;
  }       loc;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
    unsigned  length;
    unsigned short  repeat;
  }       chars;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
              asmint expression;
    unsigned short  repeat;
  }       value;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
    short   optype;
    unsigned  fillword;
    unsigned  opint;

    /* ** fill in ** */
  }       option;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
          asmreg basereg1:           7;
          asmreg basereg2:           7;
  }       alias;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
unsigned  fill03:           6;
#ifndef V210
          asmopcode op:           8;
unsigned:           2;		/* to bring to wd bdry */
          asmreg reg1:           7;
          asmreg reg2:           7;
          asmformat form:           4;
          asmreg reg3:           7;
#else
          asmopcode op:	9;
unsigned: 1;
          asmreg reg1:           8;
          asmreg reg2:           8;
          asmformat form:           8;
          asmreg reg3:           8;
#endif
  }       rinst;
  struct {
    asmsym symno;
unsigned  fill0a:           10;
unsigned  asmtype:           6;
unsigned  fill03:           6;
#ifndef V210 
          asmopcode op:           8;
unsigned:           2;		/* to bring to wd bdry */
          asmreg reg1:           7;
          asmreg reg2:           7;
          asmformat form:           4;
#else
         asmopcode op:	9;
unsigned: 1;
          asmreg reg1:           8;
          asmreg reg2:           8;
          asmformat form:           8;
#endif
              asmint immediate;
  }       iinst;
} binasm;

#endif


