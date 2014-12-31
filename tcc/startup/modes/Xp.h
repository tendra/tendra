/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * STARTUP FILE FOR COMPILATION MODE XP
 *
 * Xp represents ANSI C with a few extra portability checks. Nothing
 * too drastic. This mode is suitable for checking portability to
 * 32-bit machines.
 */

#pragma TenDRA declaration block Xp__startup begin
#pragma TenDRA begin

#include "../literal/c89.h"
#include "../promotion/c89.h"

#pragma TenDRA conversion analysis (int-pointer explicit) warning
#pragma TenDRA function pointer as pointer warning
#pragma TenDRA weak prototype analysis on
#pragma TenDRA implicit function declaration warning
#pragma TenDRA implicit int type for function return warning
#pragma TenDRA incompatible interface declaration warning
#pragma TenDRA incompatible void return warning
#pragma TenDRA fall into case warning
#pragma TenDRA unreachable code warning

#pragma TenDRA linkage resolution : (internal) warning

#pragma TenDRA unknown pragma warning

#pragma TenDRA declaration block end

