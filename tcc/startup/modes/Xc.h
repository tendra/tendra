/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * STARTUP FILE FOR COMPILATION MODE XC
 *
 * Xc represents strict language compliance, no more, no less.
 * Which means (in theory) there should be nothing to do here.
 */

#pragma TenDRA declaration block Xc_startup begin
#pragma TenDRA begin

#pragma TenDRA weak prototype analysis off
#pragma TenDRA incompatible interface declaration warning

#pragma TenDRA linkage resolution : (internal) warning

#pragma TenDRA unknown pragma allow
#pragma TenDRA no external declaration disallow

#ifndef __NO_PRINTF_CHECKS
#define __NO_PRINTF_CHECKS 1
#endif

#pragma TenDRA declaration block end

