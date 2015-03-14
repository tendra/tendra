/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MEM_COPY_H
#define MEM_COPY_H

extern void static_memory_copy(int,int,int);
extern void reverse_static_memory_copy(int,int,int);
extern void dynamic_word_memory_copy(int,int,int);
extern void reverse_dynamic_word_memory_copy(int,int,int);

#endif
