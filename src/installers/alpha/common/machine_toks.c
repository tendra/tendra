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


/* 	$Id: machine_toks.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: machine_toks.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $";
#endif /* lint */

/*
  This function recognises special tokens used by the 
  alpha installer 
*/

#include "config.h"

int machine_toks
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
  
  if(!strcmp(s,"__builtin_isfloat")){
    return 1;
  }
  if(!strcmp(s,"__builtin_va_start")){
    return 1;
  }
  if(!strcmp(s,"__builtin_va_token")){
    return 1;
  }
  if(!strcmp(s,"__alpha_special")){
    return 1;
  }
  if(!strcmp(s,"~Sync_handler")){
    return 1;
  }
  return 0;
}




