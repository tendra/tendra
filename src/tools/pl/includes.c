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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:24 $
$Revision: 1.1.1.1 $
$Log: includes.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:16  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#include "util.h"
#include "includes.h"
#include "errors.h"


char * file_name;
static Path * inc_paths;


void init_includes
    PROTO_Z ()
{
    inc_paths = MALLOC(Path);
    inc_paths->name = "";
    inc_paths->next = (Path*)0;
}

void add_include
    PROTO_N ( (p) )
    PROTO_T ( char * p )
{
    Path * x = MALLOC(Path);
    Path ** n = &inc_paths->next;
    x->name = append_string(p,"/");
    x->next = (Path*)0;
    while (*n != (Path*)0) n = &((*n)->next);
    *n = x;
}


FILE * open_include
    PROTO_N ( (a) )
    PROTO_T ( char * a )
{
    char * fn;
    Path * p = inc_paths;
    FILE * ans;
    int i;
    while(*a != '"') a++;
    a++;
    for(i=0; ; i++) {
	if (a[i]=='"' || a[i]==0) {
	    a[i] = 0;
	    break;
	}
    }
    while (p != (Path*)0) {
	fn = append_string(p->name, a);
	ans = fopen(fn,"r");
	if (ans != (FILE*)0) {
	    file_name = fn;
	    return ans;
	}
	p = p->next;
    }
    fail("Can't open include file %s", a);
    return (FILE*)0;
}
