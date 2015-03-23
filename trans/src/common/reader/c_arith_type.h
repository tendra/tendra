/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef C_ARITH_TYPE_H
#define C_ARITH_TYPE_H

int arith_type(int a, int b);
int promote(int a);
int sign_promote(int a);
variety convert(unsigned int a);

#endif

