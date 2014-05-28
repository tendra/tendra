/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef FAIL_H
#define FAIL_H

#define MAX_WARNINGS 10

typedef enum {FILE_OPEN,
	      USEAGE,
	      OVERFLOW,
	      CROSS_IMPLEMENTATION,
	      REG_ALLOC,
	      IMPLEMENTATION,
	      INSTRUCTION_OUTPUT,
	      MISC,
	      INTERNAL
	      } fail_conditions;
extern void alphafail(fail_conditions,char *,char *);
extern void failer(char *);

#define alphawarn(X)fprintf(stderr,"alphatrans: warning!: %s\n",X);

/* Error messages */

#define NO_ERROR_HANDLER       INTERNAL,"Error handler not present",""
#define TAG_NOT_IMPLEMENTED    IMPLEMENTATION,"Unimplemented tag",""
#define BIG_LABEL		IMPLEMENTATION,"64 bit labels not supported",""
#define BIG_MULTIPLICATION	OVERFLOW,"64 bit multiplication failed",""
#define BIG_DIVISION		OVERFLOW,"64 bit division failed",""
#define BIG_ADDITION		OVERFLOW,"64 bit addition failed",""
#define BIG_SUBTRACTION	OVERFLOW,"64 bit subtraction failed",""
#define ILLEGAL_FLAG		USEAGE,"Illegal flag"
#define CANNOT_OPEN_FILE	FILE_OPEN,""
#define OUT_OF_TREGS		REG_ALLOC,"Too many fixed point t-regs required",""
#define OUT_OF_F_TREGS		REG_ALLOC,"Too many floating point t-regs required",""
#define ILLEGAL_BLOCK_COPY	REG_ALLOC,"illegal block copy.  This should not happen",""
#endif
