/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READ_SORT_H
#define READ_SORT_H

/*
 * read_sort  calls the decoder routine for the sort given by sn and delivers
 * the result inserted into the union tokval
 */
tokval read_sort(int sn);

#endif /* READ_SORT_H */
