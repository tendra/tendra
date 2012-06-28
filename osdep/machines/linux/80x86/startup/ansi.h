/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* TODO: split these by os/cpu, and move up to common/ directories */
#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(posix)
#unassert lint
#endif

#ifdef _GLIBC2_12
#define __STRICT_ANSI__
#endif

