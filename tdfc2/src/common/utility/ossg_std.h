/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OSSG_STD_INCLUDED
#define OSSG_STD_INCLUDED


/*
    STANDARD C HEADER

    These pragmas describe the extra checks to be applied to the program
    by the TenDRA C compiler.  They encapsulate the coding standard to
    be applied.
*/

#ifdef __TenDRA__

#pragma TenDRA begin

#pragma TenDRA complete struct/union analysis warning
#pragma TenDRA conversion analysis (int-int implicit) warning
#pragma TenDRA conversion analysis (int-pointer) warning
#pragma TenDRA conversion analysis (pointer-pointer) warning
#pragma TenDRA discard analysis warning
#pragma TenDRA implicit function declaration off
#pragma TenDRA incompatible interface declaration disallow
#pragma TenDRA incompatible void return disallow
#pragma TenDRA variable analysis on
#pragma TenDRA weak prototype analysis on

#pragma TenDRA linkage resolution : (internal) warning
#pragma TenDRA no external declaration disallow
#pragma TenDRA initialization of struct/union (auto) disallow
#pragma TenDRA text after directive disallow
#pragma TenDRA unknown escape disallow
#pragma TenDRA unknown pragma warning

#ifndef OLD_PRODUCER
#pragma TenDRA fall into case warning
#pragma TenDRA unreachable code warning
#endif

#undef __NO_PRINTF_CHECKS

#endif


#endif
