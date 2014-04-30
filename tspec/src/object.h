/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <shared/bool.h>

/*
 * FORWARD STRUCTURE DECLARATIONS
 *
 * A number of types are defined recursively, these are declared here.
 */
struct field_tag;
struct info_tag;
struct type_tag;

/*
 * OBJECT TYPES
 *
 * These values give the various values for the objtype field of an
 * object.  For each object type, the corresponding field of the union
 * is given.
 */
enum obj_type {
	OBJ_CONST,     /* u_type */
	OBJ_DEFINE,    /* u_str */
	OBJ_ENUM,      /* u_type */
	OBJ_ENUMVAL,   /* u_str */
	OBJ_EXP,       /* u_type */
	OBJ_EXTERN,    /* u_type */
	OBJ_FIELD,     /* u_field */
	OBJ_FILE,      /* u_file */
	OBJ_FUNC,      /* u_type */
	OBJ_IF,        /* u_iftype */
	OBJ_IMPLEMENT, /* u_obj */
	OBJ_MACRO,     /* u_str */
	OBJ_NAT,       /* none */
	OBJ_SET,       /* u_obj */
	OBJ_STATEMENT, /* u_type */
	OBJ_SUBSET,    /* u_info */
	OBJ_TEXT_INCL, /* none */
	OBJ_TEXT_SRC,  /* none */
	OBJ_TOKEN,     /* u_obj or u_str */
	OBJ_TYPE,      /* u_type */
	OBJ_USE,       /* u_obj */
	OBJ_WEAK,      /* u_type */
	OBJ_KEYWORD,   /* u_num */
	OBJ_DEFMIN     /* u_str */
};

/*
 * SUBTYPES FOR IF STATEMENTS
 *
 * Objects of type OBJ_IF are classified by an enumeration indicating
 * the corresponding directive.
 */
enum obj_iftype {
	CMD_END,
	CMD_IF,
	CMD_IFDEF,
	CMD_IFNDEF,
	CMD_ELSE,
	CMD_ENDIF,
	CMD_NONE
};

/*
 * TYPE REPRESENTING AN OBJECT
 *
 * This type is used to represent a general object of list of objects.
 * Each object has an associated name, an object type, a union giving
 * different information for different object types, and a pointer to
 * the next object.
 */
typedef struct object_tag {
	char *name;
	enum obj_type objtype;

	union {
		int u_num;
		enum obj_iftype u_iftype;
		char *u_str;
		FILE *u_file;
		struct field_tag *u_field;
		struct info_tag *u_info;
		struct object_tag *u_obj;
		struct type_tag *u_type;
	} u;

	struct object_tag *next;
	char *filename;
	int line_no;
} object;

/*
 * SUBSET INFORMATION
 *
 * This routine is used to represent subset information.
 */
typedef struct info_tag {
	char *api, *file, *subset;
	time_t age;
	char *incl, *src;
	char *block;
	char *linkage;
	char *nspace;
	char *method;
	char *prefix;
	char *protect;
	char *version;
	bool tokens;
	int implemented;
	object *elements;
} info;

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with creating and manipulating objects.
 */
object *make_object(char *, int);
object *join_object(object *, object *);
object *make_subset(char *);
info *make_info(char *, char *, char *);
object *make_token(char *, int, object *, int);
object *make_exp(char *, int, int);
void update_time(object *, object *);

#endif

