/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAIN_DRIVER_H
#define MAIN_DRIVER_H

struct driver {
	const char *version;

	void (*init)(void);
	void (*unhas)(void);
	void (*main)(FILE *f);

	const char *opts;
	int (*option)(char c, const char *optarg);
	int (*cpu)(const char *optarg);

	/* permitted sets */
	unsigned abi;
	unsigned cconv;
	unsigned endian;
	unsigned format;
	unsigned diag;
	unsigned assembler;
};

extern struct driver driver;

#endif

