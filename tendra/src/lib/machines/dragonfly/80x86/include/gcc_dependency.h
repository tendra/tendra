/*
 *  $TenDRA: tendra/src/lib/machines/dragonfly/80x86/include/gcc_dependency.h,v 1.2 2004/03/27 18:14:52 stefanf Exp $
 */
#ifndef		__FREEBSD_GCC_DEPENDENCY_H__
#define		__FREEBSD_GCC_DEPENDENCY_H__

/*
 *  Currently, FreeBSD uses non-ISO extensions to the C language
 *  created by the GNU Free Software Foundation's gcc compiler.  To
 *  permit these extensions in TenDRA, the following pragma is needed.
 *  More details are at:
 *
 *     tendra/src/producers/common/parse/psyntax.sid
 *
 *  and the C Checker Reference Manual,
 */

#pragma TenDRA unknown directive warning

#endif /* __FREEBSD_GCC_DEPENDENCY_H__ */
