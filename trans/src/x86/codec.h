/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODEC_H
#define CODEC_H

#include <local/ash.h>

#include <reader/exp.h>

void codec(where dest, ash stack, exp e);
void uop(void(*op)(shape, where, where), shape sha, exp a, where dest, ash stack);
void bop(void(*op)(shape, where, where, where), shape sha, exp a, exp b, where dest, ash stack);
int is_crc(exp e);

#endif /* CODEC_H */
