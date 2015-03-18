/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef EXTERNAL_H
#define EXTERNAL_H


/*
 * EXTERNAL INTERFACE SPECIFICATION
 *
 * This header describes the non-ANSI component of the program API.
 */

#define _POSIX_SOURCE

#include <sys/types.h>
#include <sys/wait.h>

typedef int wait_type;
#define process_wait(X)		wait((X))
#define process_return(X, Y)	((X) = (Y))
#define process_exited(X)	WIFEXITED((X))
#define process_signaled(X)	WIFSIGNALED((X))
#define process_exit_value(X)	WEXITSTATUS((X))
#define process_signal_value(X)	WTERMSIG((X))

#endif /* EXTERNAL_H */
