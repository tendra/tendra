/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/sym.h,v 1.2.17.2 1998/04/28 15:14:01 Randy_Lowell Exp $ */
#ifndef _SYM_H
#define _SYM_H

/* (C) Copyright 1984 by Third Eye Software, Inc.
 *
 * Third Eye Software, Inc. grants reproduction and use rights to
 * all parties, PROVIDED that this comment is maintained in the copy.
 *
 * Third Eye makes no claims about the applicability of this
 * symbol table to a particular use.
 */
/* 
 * This file contains the definition of the Third Eye Symbol Table.
 *
 * Symbols are assumed to be in 'encounter order' - i.e. the order that
 * the things they represent were encountered by the compiler/assembler/loader.
 * EXCEPT for globals!	These are assumed to be bunched together,
 * probably right after the last 'normal' symbol.  Globals ARE sorted
 * in ascending order.
 *
 * -----------------------------------------------------------------------
 * A brief word about Third Eye naming/use conventions:
 *
 * All arrays and index's are 0 based.
 * All "ifooMax" values are the highest legal value PLUS ONE. This makes
 * them good for allocating arrays, etc. All checks are "ifoo < ifooMax".
 *
 * "isym"	Index into the SYMbol table.
 * "ipd"	Index into the Procedure Descriptor array.
 * "ifd"	Index into the File Descriptor array.
 * "iss"	Index into String Space.
 * "cb"		Count of Bytes.
 * "rgPd"	array whose domain is "0..ipdMax-1" and RanGe is PDR.
 * "rgFd"	array whose domain is "0..ifdMax-1" and RanGe is FDR.
 */


/* 
 * Symbolic Header (HDR) structure.
 * As long as all the pointers are set correctly,
 * we don't care WHAT order the various sections come out in!
 *
 * A file produced solely for the use of CDB will probably NOT have
 * any instructions or data areas in it, as these are available
 * in the original.
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

#ifdef __lint
#include <exception.h> 		/* defines struct exception_info */
#endif

typedef struct {
  unsigned short magic;		/* to verify validity of the table */
  unsigned short vstamp;	/* version stamp */
  int		 ilineMax;	/* number of line number entries */
  int		 idnMax;	/* max index into dense number table */
  int		 ipdMax;	/* number of procedures */
  int		 isymMax;	/* number of local symbols */
  int		 ioptMax;	/* byte size of optimization symbol entries */
  int		 iauxMax;	/* number of auxiliary symbol entries */
  int		 issMax;	/* max index into local strings */
  int		 issExtMax;	/* max index into external strings */
  int		 ifdMax;	/* number of file descriptor entries */
  int		 crfd;		/* number of relative file descriptors */
  int		 iextMax;	/* max index into external symbols */
  long		 cbLine;	/* number of bytes for line number entries */
  unsigned long	 cbLineOffset;	/* file offset of line number entries*/
  unsigned long	 cbDnOffset;	/* file offset of dense number table */
  unsigned long	 cbPdOffset;	/* file offset of procedure descriptor table */
  unsigned long	 cbSymOffset;	/* file offset of local symbols */
  unsigned long	 cbOptOffset;	/* file offset of optimization symbols */
  unsigned long	 cbAuxOffset;	/* file offset of auxiliary symbol entries*/
  unsigned long	 cbSsOffset;	/* file offset of local strings */
  unsigned long	 cbSsExtOffset;	/* file offset of external strings */
  unsigned long	 cbFdOffset;	/* file offset of file descriptor table */
  unsigned long	 cbRfdOffset;	/* file offset of relative file descriptors */
  unsigned long	 cbExtOffset;	/* file offset of external symbol entries */
  /* If you add machine dependent fields, add them here */
} HDRR, *pHDRR; 
#define cbHDRR sizeof(HDRR)
#define hdrNil ((pHDRR)0)

/*
 * The FDR and PDR structures speed mapping of address <-> name.
 * They are sorted in ascending memory order and are kept in
 * memory by CDB at runtime.
 */

/* 
 * File Descriptor
 *
 * There is one of these for EVERY FILE, whether compiled with
 * full debugging symbols or not.  The name of a file should be
 * the path name given to the compiler.	 This allows the user
 * to simply specify the names of the directories where the COMPILES
 * were done, and we will be able to find their files.
 *
 * Unless otherwise specified the "Base" fields are table indexes 
 * rather than byte offsets.  Likewise "count" fields give the number
 * of entries unless otherwise specified.  Together these fields identify
 * subtables which belong to the source file represented by this file
 * descriptor.
 */
typedef struct fdr {
  unsigned long	adr;	/* first text address of file */
  long	cbLineOffset;	/* start of line number entries byte offset */
  long	cbLine;		/* byte size of line entries */
  long	cbSs;		/* byte size of local string space */
  int	rss;		/* file name (of source, if known) */
  int	issBase;	/* string space byte offset */
  int	isymBase;	/* start of local symbols */
  int	csym;		/* number of local symbols */
  int	ilineBase;	/* start of expanded line numbers */
  int	cline;		/* number of expanded line numbers */
  int	ioptBase;	/* start of optimization entries byte offset */
  int	copt;		/* byte size of file's optimization entries */
  int	ipdFirst;	/* start of procedures descriptors */
  int	cpd;		/* number of procedures descriptors */
  int	iauxBase;	/* start of auxiliary entries */
  int	caux;		/* number of file's auxiliary entries */
  int	rfdBase;	/* start of file indirect table entries */
  int	crfd;		/* number of file indirect entries */
  unsigned int	lang: 5;	/* language for this file */
  unsigned int	fMerge : 1;	/* whether this file can be merged */
  unsigned int	fReadin : 1;	/* true if it was read in (not just created) */
  unsigned int	fBigendian : 1;	/* if set, was compiled on big endian machine
				 * aux's will be in compile host's sex 
				 */
  unsigned int	glevel : 2;	/* level this file was compiled with */
  unsigned int	fTrim : 1;	/* whether the symbol table was trimmed */
  unsigned int	reserved : 5;	/* reserved for future use */
  unsigned short vstamp;	/* in a linked object, the value of HDRR.vstamp
				 * in the .o file input to the linker 
				 */
  unsigned int	reserved2;
} FDR, *pFDR;
#define cbFDR sizeof(FDR)
#define fdNil ((pFDR)0)
#define ifdNil -1
#define ifdTemp 0
#define ilnNil -1


/* 
 * Procedure Descriptor
 *
 * There is one of these for EVERY TEXT LABEL.
 * If a procedure is in a file with full symbols, then isym
 * will point to the PROC symbols, else it will point to the
 * global symbol for the label.
 *
 * Table offsets are relative to the subtable ranges of the containing
 * file descriptor.
 */

typedef struct pdr {
  unsigned long	 adr;		/* first text address of procedure */
  long		 cbLineOffset;	/* byte offset for this procedure */
  int		 isym;		/* start of local symbol entries */
  int		 iline;		/* start of line number entries*/
  unsigned int	 regmask;	/* save register mask */
  int		 regoffset;	/* save register offset (reg_frame == 0)
				 * save-ra register number (reg_frame == 1) 
				 */
  int		 iopt;		/* byte offset of optimization symbols */
  unsigned int	 fregmask;	/* save floating point register mask */
  int		 fregoffset;	/* save floating point register offset */
  int		 frameoffset;	/* frame size */
  int		 lnLow;		/* lowest line in the procedure */
  int		 lnHigh;	/* highest line in the procedure */
  unsigned int	 gp_prologue:8;	/* byte size of GP prologue */
  unsigned int	 gp_used : 1;	/* true if the procedure uses GP */
  unsigned int	 reg_frame : 1;	/* true if register frame procedure */
  unsigned int	 prof : 1;	/* true if compiled with -pg */
  unsigned int	 reserved : 13;	/* reserved: must be zero */
  unsigned int	 localoff : 8;	/* offset of local variables from vfp */
  unsigned short framereg;	/* frame pointer register */
  unsigned short pcreg;		/* offset or reg of return pc */
} PDR, *pPDR;
#define cbPDR sizeof(PDR)
#define pdNil ((pPDR) 0)
#define ipdNil	-1

/*
 * The structure of the runtime procedure descriptor created by the loader
 * for use by the static exception system.
 */
struct exception_info;

typedef struct runtime_pdr {
  unsigned long	 adr;		/* memory address of start of procedure */
  unsigned int	 regmask;	/* save register mask */
  int		 regoffset;	/* save register offset */
  unsigned int	 fregmask;	/* save floating point register mask */
  int		 fregoffset;	/* save floating point register offset */
  int		 frameoffset;	/* frame size */
  unsigned short framereg;	/* frame pointer register */
  unsigned short pcreg;		/* offset or reg of return pc */
  int		 irpss;		/* index into the runtime string table */
  unsigned int	 reserved;
  struct exception_info *exception_info;/* pointer to exception array */
} RPDR, *pRPDR;
#define cbRPDR sizeof(RPDR)
#define rpdNil ((pRPDR) 0)

/*
 * Line Numbers
 *
 * Line Numbers are segregated from the normal symbols because they
 * are [1] smaller , [2] are of no interest to your
 * average loader, and [3] are never needed in the middle of normal
 * scanning and therefore slow things down.
 *
 * By definition, the first LINER for any given procedure will have
 * the first line of a procedure and represent the first address.
 */

typedef	int LINER, *pLINER;
#define lineNil ((pLINER)0)
#define cbLINER sizeof(LINER)
#define ilineNil	-1



/*
 * The Symbol Structure
 */

typedef struct {
  long		value;		/* value of symbol */
  int		iss;		/* index into String Space of name */
  unsigned int	st : 6;		/* symbol type */
  unsigned int	sc : 5;		/* storage class - text, data, etc */
  unsigned int	reserved : 1;	/* reserved */
  unsigned int	index : 20;	/* index into sym/aux table */
} SYMR, *pSYMR;
#define symNil ((pSYMR)0)
#define cbSYMR sizeof(SYMR)
#define isymNil -1
#define indexNil ((long)0xfffff)
#define issNil -1
#define issNull 0


/* E X T E R N A L   S Y M B O L  R E C O R D
 *
 *	Same as the SYMR except it contains file context to determine where
 *	the index is.  The SYMR's iss field points into the external string
 *	table.
 */
typedef struct {
  SYMR		asym;		/* symbol for the external */
  unsigned int	jmptbl:1;	/* symbol is a jump table entry for shlibs */
  unsigned int	cobol_main:1;	/* symbol is a cobol main procedure */
  unsigned int	weakext:1;	/* symbol is weak external */
  unsigned int	reserved:29;	/* reserved for future use */
  int	ifd;		/* where the index field points into */
} EXTR, *pEXTR;
#define extNil ((pEXTR)0)
#define cbEXTR sizeof(EXTR)


/* A U X I L I A R Y   T Y P E	 I N F O R M A T I O N
 *
 * Auxiliary information describes the type of each symbol.  The number
 * of AUX records required to describe a type depends upon the complexity
 * of that type.  The first record for a type is denoted by the index
 * field of a SYMR record.
 *
 * Types are composed of a basic type with zero or more type qualifiers.
 * A basic type is a core type supported by a language such as "integer",
 * "character", or "floating point".  Some basic types such as "structure"
 * or "set" can reference other types or other symbols.
 *
 * A type qualifier is a modifier for a type such as "pointer to", or
 * "array of".  If a type has more than one qualifier, they are ordered
 * from lowest to highest.  Lower qualifiers are applied to the basic
 * type before higher qualifiers.  To illustrate this, consider a
 * complex type such as "array of pointers to integers".  The basic type
 * for this is "integer" and there are two qualifiers, "array of" and
 * "pointer to".  Each element of the array is a "pointer to integer".
 * Therefore, the qualifier "pointer to" must be applied to the basic
 * type "integer" first.  In this example, the qualifier "pointer to" is
 * lower than the qualifier "array of".
 *
 * With this background, we can describe the structure of a type
 * description.  AUX records must be decoded by starting at the first
 * record for a type description and decoding each successive record in
 * the context of the previous records.  The following steps define an
 * algorithm for consuming AUX records and decoding a type description.
 * The numbered steps must be followed in order to consume the AUX
 * records correctly.
 *
 * 	1. If this type description is pointed at by a symbol with type
 * 	   stProc or stStaticProc, the first AUX is interpreted as an
 * 	   'isym'.  Its value is the index of the local symbol table entry
 * 	   that follows the procedure's stEnd symbol.
 *
 * 	2. The next AUX is always a TIR record.  This record contains
 * 	   the basic type and the first few type qualifiers.  If more
 * 	   type qualifiers are required, the TIR record has its
 * 	   'continued' field set.  The type qualifiers are numbered from
 * 	   0 to 5.  Qualifier 0 is the "lowest" (in the sense defined above).
 *
 * 	3. If the TIR record has its 'fBitfield' field set, the next
 * 	   AUX is interpreted as a 'width'.  The width is the size, in
 * 	   bits, of the type.
 *
 * 	4. The next AUX depends upon the basic type in the TIR record.
 * 	   If the next AUX is an RNDXR record, it may occupy either one
 * 	   or two AUX records.  See the RNDXR definition below for
 * 	   details.
 *
 * 		A) If the basic type is btStruct, btUnion, btEnum,
 * 		   btClass, or btTypedef; the next AUX is an RNDXR
 * 		   record.  The 'index' field of the RNDXR points into
 * 		   the local symbol table.  The specified local symbol is
 * 		   the start of the definition of the structure, union,
 * 		   enumeration, class or typedef.
 *
 * 		B) If the basic type is btSet, the next AUX is also an
 * 		   RNDXR.  The 'index' field of the RNDXR points into
 * 		   the AUX table.  The specified AUX record is the start
 * 		   of the description of the type of each element in the
 * 		   set.
 *
 * 		C) If the basic type is btIndirect, the next AUX is
 * 		   again an RNDXR whose 'index' field points into the
 * 		   AUX table.  The specified AUX record is the start of
 * 		   the description of the referenced type.
 *
 * 		D) If the basic type is btRange, the next three AUX
 * 		   records are used.  The next AUX is an RNDXR whose
 * 		   'index' field points into the AUX table.  The
 * 		   specified AUX is the start of the description of the
 * 		   type being subranged.  The AUX following the RNDXR is
 * 		   interpreted as a 'dnLow'.  This is the low bound of
 * 		   the range.  The final AUX is interpreted as a
 * 		   'dnHigh' and is the high bound of the range.
 *
 * 	5. The next AUX depends on the type qualifiers in the TIR record.
 * 	   Information for lower numbered type qualifiers is stored
 * 	   before information for higher numbered qualifiers.
 *
 * 		A) Each tqArray qualifier has four additional AUX
 * 		   records.  The first is an RNDXR whose index field
 * 		   points into the AUX table.  The AUX specified by this
 * 		   RNDXR is the type of the index into the array.  The
 * 		   AUX following the RNDXR is interpreted as a 'dnLow'.
 * 		   This is the low dimension of the array.  The next AUX
 * 		   is interpreted as a 'dnHigh' and is the high
 * 		   dimension.  The final AUX is interpreted as a
 * 		   'width'.  This is the size in bits of each element in
 * 		   the array.
 *
 * 	6. If the TIR record has its 'continued' field set, the next AUX
 * 	   is another TIR record.  Only the type qualifier and
 * 	   'continued' fields of this TIR are important.  The qualifiers
 * 	   in this TIR are all "higher" than the qualifiers in the previous
 * 	   TIR.  Additional AUX records are decoded as described in step 5.
 * 	   If this TIR has its 'continued' field set, repeat step 6.  The
 * 	   process stops when we reach a TIR with its 'continued' field
 * 	   cleared.
 */

/*
 * Type Information Record
 */
typedef struct {
  unsigned int	fBitfield : 1;	/* set if bit width is specified */
  unsigned int	continued : 1;	/* indicates additional TQ info to follow */
  unsigned int	bt  : 6;	/* basic type */
  unsigned int	tq4 : 4;
  unsigned int	tq5 : 4;
  /* ---- 16 bit boundary ---- */
  unsigned int	tq0 : 4;
  unsigned int	tq1 : 4;	/* 6 type qualifiers - tqPtr, etc. */
  unsigned int	tq2 : 4;
  unsigned int	tq3 : 4;
} TIR, *pTIR;
#define cbTIR sizeof(TIR)
#define tiNil ((pTIR)0)
#define itqMax 6

/*
 * Relative symbol record
 *
 * If the rfd field is ST_RFDESCAPE, the isym field of the next AUX record is
 * the index into the file indirect table.
 */

typedef struct {
  unsigned int	rfd : 12;	/* index into the file indirect table */
  unsigned int	index : 20;	/* index int sym/aux/iss tables */
} RNDXR, *pRNDXR;
#define cbRNDXR sizeof(RNDXR)
#define rndxNil ((pRNDXR)0)

/* a union of all possible info in the AUX universe */
typedef union {
  TIR		ti;		/* type information record */
  RNDXR		rndx;		/* relative index into symbol table */
  int		dnLow;		/* low dimension */
  int		dnHigh;		/* high dimension */
  int		isym;		/* symbol table index (end of proc) */
  int		iss;		/* index into string space (not used) */
  int		width;		/* width for non-default sized struc fields */
  int		count;		/* count of ranges for variant arm */
} AUXU, *pAUXU;
#define cbAUXU sizeof(AUXU)
#define auxNil ((pAUXU)0)
#define iauxNil -1


/*
 * Optimization symbols
 *
 * Optimization symbols consist of a sequence of zero or more "per
 * procedure optimization descriptions" (PPOD).  Each PPOD is pointed
 * to by the "iopt" field of the procedure descriptor (PDR).
 */

typedef struct {
  unsigned int	ppode_tag;
  unsigned int	ppode_len;
  unsigned long	ppode_val;
} PPODHDR, *pPPODHDR;

/* The pOPTR type below must be used when calculating offsets within the
 * optimization symbols section.  The optimization symbol section is 
 * composed of both PPODHDR entries and freeform data, so counts and 
 * offsets within the section are recorded in bytes.
 */

#define cbOPTR   1
typedef char OPTR;
typedef char *pOPTR;
#define optNil	((pOPTR) 0)
#define ioptNil -1

/*
 * Dense number record
 *
 * Rather than use file index, symbol index pairs to represent symbols
 *	and globals, we use dense number so that they can be easily embedded
 *	in intermediate code and the programs that process them can
 *	use direct access tables instead of hash table (which would be
 *	necessary otherwise because of the sparse name space caused by
 *	file index, symbol index pairs.  Ucode uses the term block
 *	number instead of dense number.
 *
 * If the rfd field is ST_EXTIFD, the index field points into the external
 *	symbol table.  If the index field is ST_ANONINDEX, it is an anonymous
 *	entry and does not index any table.
 */
typedef struct {
  unsigned int	rfd;	/* index into the file table */
  unsigned int	index;	/* index into sym table */
} DNR, *pDNR;
#define cbDNR sizeof(DNR)
#define dnNil ((pDNR)0)


/*
 * File Indirect
 *
 * When a symbol is referenced across files the following procedure is used:
 *	1) use the file index to get the File indirect entry.
 *	2) use the file indirect entry to get the File descriptor.
 *	3) add the sym index to the base of that file's sym table
 *
 */

typedef int RFDT, *pRFDT;
#define cbRFDT sizeof(RFDT)
#define rfdNil	-1

/*
 * The file indirect table is simply another name used by the linker for the 
 * relative file descriptors.
 */
typedef int FIT, *pFIT;
#define cbFIT	sizeof(FIT)
#define ifiNil	-1
#define fiNil	((pFIT) 0)

#endif	/* __LANGUAGE_C__ */

#ifdef __LANGUAGE_PASCAL__
#define ifdNil -1
#define ilnNil -1
#define ipdNil -1
#define ilineNil -1
#define isymNil -1
#define indexNil 16#fffff
#define issNil -1
#define issNull 0
#define itqMax 6
#define iauxNil -1
#define ioptNil -1
#define rfdNil -1
#define ifiNil -1
#endif	/* __LANGUAGE_PASCAL__ */


/*
 * The following table defines the meaning of each SYM field as
 * a function of the "st". (scD/B is any of scData, scSData, scBss,
 * scSBss, scRData, or scRConst)
 *
 * Note: the value "isymMac" is used by symbols that have the concept
 * of enclosing a block of related information.	 This value is the
 * isym of the first symbol AFTER the end associated with the primary
 * symbol. For example if a procedure was at isym==90 and had an
 * isymMac==155, the associated end would be at isym==154, and the
 * symbol at 155 would probably (although not necessarily) be the
 * symbol for the next procedure.  This allows rapid skipping over
 * internal information of various sorts. "stEnd"s ALWAYS have the
 * isym of the primary symbol that started the block.
 * 

ST		SC	VALUE		INDEX
--------	------	--------	------
stFile		scText	-------		isymMac
stLabel		scText	address		---
stGlobal	scD/B	address		iaux
stStatic	scD/B	address		iaux
stParam		scAbs	offset		iaux
stLocal		scAbs	offset		iaux
stProc		scText	address		iaux	(isymMac is first AUX)
stStaticProc	scText	address		iaux	(isymMac is first AUX)

stMember	scNil	ordinal		---	(if member of enum)
stMember	scNil	byte offset	iaux	(if member of struct/union)
stMember	scBits	bit offset	iaux	(bit field spec)

stBlock		scText	offset		isymMac (text block, offset from proc)
stBlock		scNil	cb		isymMac (struct/union member define)
stBlock		scNil	cMembers	isymMac (enum member define)

stEnd		scText	offset		isymStart (offset from proc start)
stEnd		scNil	-------		isymStart (struct/union/enum)

stTypedef	scNil	-------		iaux
stRegReloc	sc???	value		old register number
stForward	sc???	new address	isym to original symbol

stConstant	scInfo	value		--- (scalar)
stConstant	scInfo	iss		--- (complex, e.g. string)

 *
 */
#endif
