/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CHECK_INCLUDED
#define CHECK_INCLUDED

typedef struct NAME_tag {
    int type;
    char *text[3];
    const char *file;
    int line;
    struct NAME_tag *next;
} NAME;

#define NAME_TYPE		0
#define NAME_TYPE_AUX		1
#define NAME_ENUM_CONST		2
#define NAME_STRUCT_CMP		3
#define NAME_UNION_CMP		4
#define NAME_FIELD_CMP		5
#define NAME_MAP		6
#define NAME_MAP_ARG		7
#define NAME_LAST		8

extern void check_names(int);

#endif
