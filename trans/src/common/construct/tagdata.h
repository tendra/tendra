/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_TAGDATA_H
#define CONSTRUCT_TAGDATA_H

typedef struct tag_option_t {
	bool present;
	/* 1 if val is present, 0 otherwise */
	tag val;
} tag_option;

typedef struct string_option_t {
	bool present;
	string val;
} string_option;

typedef struct tagsh_t {
	shape sha;
	access visible;
	tag tag;
} tagshacc;

typedef struct tagsh_list_t {
	exp id;
	exp last_def;
	exp last_id;
	exp proc_def;
	int size;
	int number;
} tagshacc_list;

typedef struct tagacc_t {
	tag tag;
	access visible;
} tagacc;

typedef struct tagacc_option_t {
	bool present;	/* 1 if val is present, 0 otherwise */
	tagacc val;
} tagacc_option;

typedef  struct labtag_t {
	label place_label;
} labtag;

struct labtag_list_t {
	label *elems;
	int number;	/* number labels */
};
typedef struct labtag_list_t label_list;

typedef struct tagshacc_option_t {
	int present;	/* 1 if val is present, 0 otherwise */
	tagshacc val;
} tagshacc_option;


#endif

