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
	void (*binasm)(void);
	void (*symtab)(void);
	void (*cleanup)(void);

	const char *opts;
	int (*option)(char c, const char *optarg);
	int (*cpu)(const char *optarg);

	void (*translate_capsule)(void);

	/* permitted sets */
	unsigned abi;
	unsigned cconv;
	unsigned endian;
	unsigned format;
	unsigned diag;
	unsigned assembler;
};

extern struct driver driver;

extern FILE *as_file;
extern FILE *ba_file;
extern FILE *st_file;

void local_translate_capsule(void);

#endif

