/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef HPPA_LABEXP_H
#define HPPA_LABEXP_H


struct labexp_t {
    exp e;
    int lab;
    struct labexp_t *next;
};

typedef struct labexp_t *labexp;

#endif

