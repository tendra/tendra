/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TDF_NAME_H
#define TDF_NAME_H

const char *getname(int n);
const char *find_test_name(int n); /* call with test_number(e) */
const char *shape_name(int n);

#endif

