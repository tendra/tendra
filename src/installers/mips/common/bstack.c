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
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: bstack.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/12  10:59:13  currie
 * gcc pedanttry
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
#include "config.h"
#include "xalloc.h"
#include "bstack.h"

void push
    PROTO_N ( (symval, strval, stack) )
    PROTO_T ( long symval X long strval X BSTACK *stack )
{
	while (stack->nextspace!=0) {stack=stack->nextspace;}
	if (stack->pos < STACKSIZE)
		{stack->symind[stack->pos]=symval;
		stack->strind[stack->pos]=strval;
		stack->pos+=1;
		}
	else
		{stack->nextspace=(BSTACK*)xcalloc(1,sizeof(BSTACK));
		stack->nextspace->symind[0]=symval;
		stack->nextspace->strind[0]=strval;
		stack->nextspace->pos=1;
		}
}


SYMSTR pop
    PROTO_N ( (stack) )
    PROTO_T ( BSTACK *stack )
{
	SYMSTR retval;
	BSTACK* oldstack=(BSTACK*)xcalloc(1,sizeof(BSTACK));
	oldstack=stack;
	while (stack->nextspace!=0)
		{oldstack=stack;
		stack=stack->nextspace;}
	if (stack->pos==0)
		{stack=oldstack;
		xfree(stack->nextspace);
		retval.sym = stack->symind[STACKSIZE-1];
		retval.str = stack->strind[STACKSIZE-1];
		stack->nextspace = (BSTACK*)0;
		stack->pos=STACKSIZE-1;
		}
	else	{retval.sym=stack->symind[stack->pos-1];
		retval.str=stack->strind[stack->pos-1];
		stack->pos-=1;
		}
	return retval;
}
