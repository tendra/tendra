/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DYNAMIC_INIT_H
#define DYNAMIC_INIT_H

extern int do_dynamic_init;

extern void do__main_extern(void);
extern void call__main(void);
extern int proc_is_main(exp);

#endif
