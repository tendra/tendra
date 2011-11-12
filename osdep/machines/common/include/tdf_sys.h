/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    COMPILATION MODE APPLIED TO SYSTEM HEADERS
    This file describes the compilation mode which is applied to the
    system headers.  Basically everything is turned off.
*/

#ifndef __TDF_SYS_MODE_INCLUDED
#define __TDF_SYS_MODE_INCLUDED

#pragma TenDRA begin name environment NO_CHECKS
#pragma TenDRA no external declaration allow
#pragma TenDRA complete struct/union analysis off
#pragma TenDRA conversion analysis off
#pragma TenDRA directive assert allow
#pragma TenDRA directive file allow
#pragma TenDRA directive ident allow
#pragma TenDRA directive include_next allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive weak allow
#pragma TenDRA discard analysis off
#pragma TenDRA extra bitfield int type allow
#pragma TenDRA extra type definition allow
#pragma TenDRA fall into case allow
#pragma TenDRA function pointer as pointer allow
#pragma TenDRA ignore struct/union/enum tag on
#pragma TenDRA implicit function declaration on
#pragma TenDRA implicit int type for external declaration allow
#pragma TenDRA implicit int type for function return allow
#pragma TenDRA incompatible interface declaration allow
#pragma TenDRA incompatible void return allow
#pragma TenDRA indented # directive allow
#pragma TenDRA initialization of struct/union (auto) allow
#pragma TenDRA prototype allow
#pragma TenDRA text after directive allow
#pragma TenDRA unknown escape allow
#pragma TenDRA unknown pragma allow
#pragma TenDRA unreachable code allow
#pragma TenDRA variable analysis off
#pragma TenDRA weak macro equality allow
#pragma TenDRA weak prototype analysis off
#pragma TenDRA end

#pragma TenDRA directory SYSTEM use environment NO_CHECKS
#pragma TenDRA directory SYSTEM1 use environment NO_CHECKS
#pragma TenDRA directory SYSTEM2 use environment NO_CHECKS

#pragma TenDRA ident ... allow

#endif
