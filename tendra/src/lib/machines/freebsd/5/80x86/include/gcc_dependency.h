/*
 *  $TenDRA: tendra/src/lib/machines/freebsd/5/80x86/include/gcc_dependency.h,v 1.1 2003/02/18 07:35:09 asmodai Exp $
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
