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
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: xalloc.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/


#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "messages_r.h"
#include "xalloc.h"

voidstar xcalloc
    PROTO_N ( (n, s) )
    PROTO_T ( int n X size_t s )
{
  if (n == 0)
    return ((voidstar) 0);
  {
    voidstar v = (voidstar) calloc ((size_t)n, s);
    if (v == (voidstar) 0) {
      failer (NO_MEMORY);
      exit (EXIT_FAILURE);
    }
    return (v);
  }
}

voidstar xrealloc
    PROTO_N ( (p, s) )
    PROTO_T ( voidstar p X size_t s )
{
  voidstar v = (voidstar) realloc (p, s);
  if (v == (voidstar) 0) {
    failer (NO_MEMORY);
    exit (EXIT_FAILURE);
  }
  return v;
}

void xfree
    PROTO_N ( (p) )
    PROTO_T ( voidstar p )
{
   if (p)
     free(p);
   return;
}

voidstar xmalloc
    PROTO_N ( (s) )
    PROTO_T ( size_t s )
{
  voidstar v = (voidstar) malloc (s);
  if (s != (size_t)0 && v == (voidstar) 0) {
    failer (NO_MEMORY);
    exit (EXIT_FAILURE);
  }
  return (v);
}
