/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * STARTUP FILE FOR NO EXTRA PORTABILITY CHECKS
 *
 * nepc represents a switch for turning off most of the extra
 * conversion and weak prototype checking.
 */

#pragma TenDRA begin

#pragma TenDRA conversion analysis off
#pragma TenDRA weak prototype analysis off

#pragma TenDRA compatible type : char * == void * : allow
#pragma TenDRA function pointer as pointer allow

/* The pragmas below replace #pragma nepc */

#pragma TenDRA character escape overflow allow
#pragma TenDRA no nline after file end allow
#pragma TenDRA bitfield overflow allow

#pragma TenDRA conversion analysis (pointer-pointer implicit) off
#pragma TenDRA conversion analysis (int-pointer implicit) off

#ifndef __NO_PRINTF_CHECKS
#define __NO_PRINTF_CHECKS 1
#endif

