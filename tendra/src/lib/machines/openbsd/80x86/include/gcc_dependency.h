/*
 *  $TenDRA$
 */
#ifndef        __OPENBSD_GCC_DEPENDENCY_H__
#define        __OPENBSD_GCC_DEPENDENCY_H__

/*
 *  Currently, OpenBSD-3.2 uses non-ISO extensions to the C language
 *  created by the GNU Free Software Foundation's gcc compiler.  To
 *  permit these extensions in TenDRA, the following pragma is needed.
 *  More details are at:
 *
 *     tendra/src/producers/common/parse/psyntax.sid
 *
 *  and the C Checker Reference Manual,
 */
#pragma TenDRA unknown directive warning

#endif /* __OPENBSD_GCC_DEPENDENCY_H__ */
