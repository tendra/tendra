/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PP_H
#define PP_H
#ifndef NDEBUG
extern void showme(exp,int,int);
extern exp infotag(exp,int);
extern exp show_bro(int);
extern exp show_son(int);
extern exp show_current(int);
extern exp show_father(int);
extern exp show_pt(int);
extern exp recurse(int);
extern void properties(int);
#endif
#endif
