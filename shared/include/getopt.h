/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Public Domain, 1985, AT&T, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef GETOPT_INCLUDED
#define GETOPT_INCLUDED

extern char *optarg;
extern int optind, opterr;

int getopt(int argc, char * const *argv, const char *options);

#endif
