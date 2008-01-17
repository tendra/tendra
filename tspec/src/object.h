/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef OBJECT_INCLUDED
#define OBJECT_INCLUDED

#ifndef CONFIG_INCLUDED
#include "config.h"
#endif

/*
    FORWARD STRUCTURE DECLARATIONS

    A number of types are defined recursively, these are declared here.
*/

struct field_tag;
struct info_tag;
struct type_tag;

/*
    OBJECT TYPES

    These values give the various values for the objtype field of an
    object.  For each object type, the corresponding field of the union
    is given.
*/

enum obj_type {
	OBJ_CONST,		/* u_type */
	OBJ_DEFINE,		/* u_str */
	OBJ_ENUM,		/* u_type */
	OBJ_ENUMVAL,	/* u_str */
	OBJ_EXP,		/* u_type */
	OBJ_EXTERN,		/* u_type */
	OBJ_FIELD,		/* u_field */
	OBJ_FILE,		/* u_file */
	OBJ_FUNC,		/* u_type */
	OBJ_IF,			/* u_iftype */
	OBJ_IMPLEMENT,	/* u_obj */
	OBJ_MACRO,		/* u_str */
	OBJ_NAT,		/* none */
	OBJ_SET,		/* u_obj */
	OBJ_STATEMENT,	/* u_type */
	OBJ_SUBSET,		/* u_info */
	OBJ_TEXT_INCL,	/* none */
	OBJ_TEXT_SRC,	/* none */
	OBJ_TOKEN,		/* u_obj or u_str */
	OBJ_TYPE,		/* u_type */
	OBJ_USE,		/* u_obj */
	OBJ_WEAK,		/* u_type */
	OBJ_KEYWORD,	/* u_num */
	OBJ_DEFMIN		/* u_str */
};


/*
    SUBTYPES FOR IF STATEMENTS

    Objects of type OBJ_IF are classified by an enumeration indicating
    the corresponding directive.
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
    TYPE REPRESENTING AN OBJECT

    This type is used to represent a general object of list of objects.
    Each object has an associated name, an object type, a union giving
    different information for different object types, and a pointer to
    the next object.
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
    SUBSET INFORMATION

    This routine is used to represent subset information.
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
    boolean tokens;
    int implemented;
    object *elements;
} info;


/*
    PROCEDURE DECLARATIONS

    These routines are concerned with creating and manipulating objects.
*/

extern object *make_object(char *, int);
extern object *join_object(object *, object *);
extern object *make_subset(char *);
extern info *make_info(char *, char *, char *);
extern object *make_token(char *, int, object *, int);
extern object *make_exp(char *, int, int);
extern void update_time(object *, object *);


#endif
