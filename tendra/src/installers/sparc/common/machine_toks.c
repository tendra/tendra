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



/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/machine_toks.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: machine_toks.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1996/09/06  17:18:11  pwe
 * explicit next_callee_offset to correct double alignment
 *
 * Revision 1.6  1996/08/20  12:21:25  pwe
 * structures (etc) in varargs
 *
 * Revision 1.5  1996/08/15  15:55:19  pwe
 * add missing file headers
 *
--------------------------------------------------------------------------
*/


#include "config.h"

int machine_toks
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
/*  if (!strcmp(s, "~div"))
    return 1;
  if (!strcmp(s, "JMFprofile"))
    return 1;
  if (!strcmp(s, "JMFinline"))
    return 1;
*/
  if (!strcmp(s,"ansi.stdarg.__va_start"))
    return 1;
  if (!strcmp(s,"ansi.stdarg.va_arg"))
    return 1;
  if (!strcmp(s,"~next_caller_offset"))
    return 1;
  if (!strcmp(s,"~next_callee_offset"))
    return 1;
  if (!strcmp(s,"__sparc_special"))
    return 1;
  if(!strcmp(s,"~Sync_handler")){
    return 1;
  }
  return 0;
}
