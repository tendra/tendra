/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _HACKED_SYS_MSG_H
#define _HACKED_SYS_MSG_H

#ifdef __BUILDING_LIBS
#define msgctl	msgctl_wrong
#endif

#include_next <sys/msg.h>

#ifdef __BUILDING_LIBS
#undef msgctl
extern int msgctl ( int, int, struct msqid_ds * ) ;
#endif

#endif
