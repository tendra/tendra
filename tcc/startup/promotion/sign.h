/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* SIGNED PROMOTION RULES */

#ifndef __TCC_PROMOTION_H
#define __TCC_PROMOTION_H

#pragma token PROC ( VARIETY ) VARIETY __prom # ~sign_promote
#pragma promote char:int
#pragma promote signed char:int
#pragma promote unsigned char:unsigned int
#pragma promote short:int
#pragma promote unsigned short:unsigned int
#pragma promote int:int
#pragma promote unsigned int:unsigned int
#pragma promote long:long
#pragma promote unsigned long:unsigned long

#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA longlong type allow
#pragma promote long long:long long
#pragma promote unsigned long long:unsigned long long
#pragma TenDRA end

#pragma TenDRA begin

#pragma compute promote __prom

#pragma no_def __prom
#undef __prom
#undef __ushort_to_int

#endif

