#ifndef __HACKED_SYS_CDEFS_H
#define __HACKED_SYS_CDEFS_H

/*
 * NetBSD makes liberal use of __RENAME in its headers to provide versioning
 * for symbols. Unlike other compilers, TenDRA seperates the specification of
 * interfaces from their implementations. Here, during building of the API .tl
 * libraries for this machine, we're just interested in the interfaces.
 * So, we define __RENAME to expand out to nothing, just to get it out of the
 * way so that headers will parse.
 *
 * The mapping from API symbols (e.g. "stat") to their versioned libc
 * counterparts (e.g. "__stat30") is provided by tokens/rename_toks.tpl
 * which does the equivalent that __RENAME provides, but without involving the
 * interface.
 *
 * We define _STANDALONE just to prevent an #error from complaining that
 * function renaming is not possible.
 */
#ifdef _NETBSD5_1
#define _STANDALONE
#endif

#include_next <sys/cdefs.h>

#ifdef _NETBSD5_1
#undef __RENAME
#define __RENAME(x) /* empty */
#endif

#endif

