/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:42 $
$Revision: 1.2 $
$Log: comment.h,v $
 * Revision 1.2  1998/02/04  15:48:42  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:56  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef COMMENT_H
#define COMMENT_H

#include "config.h"

#include "exptypes.h"
#include "codetypes.h"
#include "installtypes.h"			/* for bool */


extern bool do_comment;

extern void fail(char *);


#ifdef DO_COMMENT

/* implemented as functions in comment.c */
extern void COMMENT(char *);
extern void COMMENT1(char *, long);
extern void COMMENT2(char *, long, long);
extern void COMMENT3(char *, long, long, long);
extern void COMMENT4(char *, long, long, long, long);

#else

#define COMMENT(s)			((void)0)
#define COMMENT1(s,p1)			((void)0)
#define COMMENT2(s,p1,p2)		((void)0)
#define COMMENT3(s,p1,p2,p3)		((void)0)
#define COMMENT4(s,p1,p2,p3,p4)		((void)0)

#endif


#ifdef DO_FULLCOMMENT

#define FULLCOMMENT(s)			COMMENT(s)
#define FULLCOMMENT1(s,p1)		COMMENT1(s,p1)
#define FULLCOMMENT2(s,p1,p2)		COMMENT2(s,p1,p2)
#define FULLCOMMENT3(s,p1,p2,p3)	COMMENT3(s,p1,p2,p3)
#define FULLCOMMENT4(s,p1,p2,p3,p4)	COMMENT4(s,p1,p2,p3,p4)

#else

#define FULLCOMMENT(s)			((void)0)
#define FULLCOMMENT1(s,p1)		((void)0)
#define FULLCOMMENT2(s,p1,p2)		((void)0)
#define FULLCOMMENT3(s,p1,p2,p3)	((void)0)
#define FULLCOMMENT4(s,p1,p2,p3,p4)	((void)0)

#endif

#endif				/* COMMENT_H */





