/*
 * Copyright (c) 2002, 2003, 2004 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * This code is derived from software contributed to The TenDRA Project by
 * Jeroen Ruigrok van der Werven.
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
    TYPE REPRESENTING AN OBJECT

    This type is used to represent a general object of list of objects.
    Each object has an associated name, an object type, a union giving
    different information for different object types, and a pointer to
    the next object.
*/

typedef struct object_tag {
    char *name;
    int objtype;
    union {
	int u_num;
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
    OBJECT TYPES

    These values give the various values for the objtype field of an
    object.  For each object type, the corresponding field of the union
    is given.
*/

#define OBJ_CONST		0	/* u_type */
#define OBJ_DEFINE		1	/* u_str */
#define OBJ_ENUM		2	/* u_type */
#define OBJ_ENUMVAL		3	/* u_str */
#define OBJ_EXP			4	/* u_type */
#define OBJ_EXTERN		5	/* u_type */
#define OBJ_FIELD		6	/* u_field */
#define OBJ_FILE		7	/* u_file */
#define OBJ_FUNC		8	/* u_type */
#define OBJ_IF			9	/* u_num */
#define OBJ_IMPLEMENT		10	/* u_obj */
#define OBJ_MACRO		11	/* u_str */
#define OBJ_NAT			12	/* none */
#define OBJ_SET			13	/* u_obj */
#define OBJ_STATEMENT		14	/* u_type */
#define OBJ_SUBSET		15	/* u_info */
#define OBJ_TEXT_INCL		16	/* none */
#define OBJ_TEXT_SRC		17	/* none */
#define OBJ_TOKEN		18	/* u_obj or u_str */
#define OBJ_TYPE		19	/* u_type */
#define OBJ_USE			20	/* u_obj */
#define OBJ_WEAK		21	/* u_type */
#define OBJ_KEYWORD		22	/* u_num */


/*
    SUBTYPES FOR IF STATEMENTS

    Objects of type OBJ_IF are classified by a number indicating the
    corresponding directive.
*/

#define CMD_END			0
#define CMD_IF			1
#define CMD_IFDEF		2
#define CMD_IFNDEF		3
#define CMD_ELSE		4
#define CMD_ENDIF		5
#define CMD_NONE		6


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
