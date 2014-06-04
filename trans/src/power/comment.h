/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef COMMENT_H
#define COMMENT_H

#include <reader/exp.h>

#include <reader/code.h>

#include <construct/installtypes.h>			/* for bool */

/* implemented as functions in comment.c */
extern void COMMENT(char *);
extern void COMMENT1(char *, long);
extern void COMMENT2(char *, long, long);
extern void COMMENT3(char *, long, long, long);
extern void COMMENT4(char *, long, long, long, long);


#define FULLCOMMENT(s)			COMMENT(s)
#define FULLCOMMENT1(s,p1)		COMMENT1(s,p1)
#define FULLCOMMENT2(s,p1,p2)		COMMENT2(s,p1,p2)
#define FULLCOMMENT3(s,p1,p2,p3)	COMMENT3(s,p1,p2,p3)
#define FULLCOMMENT4(s,p1,p2,p3,p4)	COMMENT4(s,p1,p2,p3,p4)

#endif				/* COMMENT_H */

