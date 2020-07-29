/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef INCLUDES_INCLUDED
#define INCLUDES_INCLUDED


extern char *file_name;

typedef struct Path_struct{
	char *name;
	struct Path_struct *next;
} Path;

extern void init_includes(void);
extern void add_include(char *);
extern FILE *open_include(char *);


#endif
