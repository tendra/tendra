/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef IBINASM
#define IBINASM


typedef enum {
	ilabel,     isym,       iglobal,    icpload,    ialign,
	iascii,     iasciiz,    ibyte,      icomm,      ilcomm,
	idata,      idouble,    ifile,      ifloat,     ihalf,
	icprestore, igpword,    icpadd,     iweakext,   iloopno,
	ispace,     itext,      iword,      iocode,     iend,
	isdata,     irdata,     ient,       iloc,       ibgnb,
	iendb,      iasm0,      iset,       icpalias,   irep,
	iendrep,    ilab,       ivreg,      imask,      ifmask,
	ierr,       iglobabs,   iverstamp,  iframe,     iextended,
	iextern,    iaent,      ioption,    inoalias,   ialias,
	imtag,      imalias,    istruct,    ilivereg, 	igjaldef,
	igjallive,  igjrlive, 	ishift_addr, irestext,  idword,
	iprologue,  iedata
    } itype;

#define n_itype 	62

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

#define zero 0
#define float_register 32
#define xnoreg 72



#define n_format 16


typedef enum {
	franone 			/* default value 		*/
	,frahi				/* reg, [reg], sym[+/-offset]	*/
	,fralo				/* reg, [reg], sym[+/-offset]	*/
	,frrel1				/* reg, .[+offset]		*/
	,frrel2				/* reg, .[-offset]		*/
	,frgprel			/* reg, sym[+/-offset] + reg    */
        ,frcprel                        /* reg, sym[reg]                */
    } format_extn;

#define  n_format_extn  7


typedef enum {
	o_undefined,
	o_optimize,
	o_pic
    } opt_type;

#define n_opt_type	 3


typedef enum {
	opt_none,
	opt_int,
	opt_float,
	opt_string
    } opt_arg_type;


typedef unsigned asmopcode;
typedef unsigned asmformat;
typedef unsigned asmreg;
typedef int asmint;
typedef unsigned asmuint;
typedef int asmlabel;
typedef int asmsym;
typedef unsigned asmformatextn;

#define zero 0
#define float_register 32


#define binasm_record_length 16

#ifndef _REG_SET_C
#define _REG_SET_C 1
typedef unsigned aligned_regset[2];
#endif /* _REG_SET_C */

typedef union {
  char data[binasm_record_length];
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
  } common;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned lexlev;
  } ent;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    asmint frameoffset;
    asmreg framereg : 7;
    asmreg pcreg : 7;
  } frame;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned regmask;
    asmint regoffset;
  } mask;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    aligned_regset gjmask;
  } gmask;
  struct {
    asmsym symno;		/* handler */
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int      flag;
    int      data;
  } edata;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int loopnum;
    unsigned lflag;
  } loopno;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int majornumber;
    int minornumber;
  } verstamp;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned filenumber;
    unsigned linenumber;
  } loc;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned gpmask;
    unsigned fpmask;
  } livereg;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned length;
    unsigned repeat;
  } chars;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    asmint expression;
    unsigned repeat;
  } value;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned option : 2;
    unsigned fill04 : 30;
    asmint opt_int_value;
  } voption;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned option : 2;
    unsigned fill04 : 30;
    asmint opt_len;
  } loption;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    asmreg basereg1 : 7;
    asmreg basereg2 : 7;
  } alias;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int tagnumber;
    int tagtype;
  } mtag;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    int memtag1;
    int memtag2;
  } malias;

  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmreg reg3 : 7;
  } rinst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    unsigned mem_tag : 14;
    asmint immediate;
  } iinst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    unsigned symoffset : 4;
    unsigned fill05 : 10;
    asmint immediate;
  } dinst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmint imm;
  } linst;
  struct {
    asmsym symno;
    unsigned fill07 : 7;
    asmformatextn formextn : 3;
    unsigned asmtype : 6;
    unsigned fill03 : 6;
    asmopcode op : 9; 
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmreg reg3 : 7;
    asmreg reg4 : 7;
  } rrinst;
} binasm;


#endif
