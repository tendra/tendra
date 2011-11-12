/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

#include <shared/xalloc.h>

#include "config.h"

#include "bstack.h"

void
push(long symval, long strval, BSTACK *stack)
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


SYMSTR
pop(BSTACK *stack)
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
