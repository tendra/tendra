/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DIAG_REFORM_H
#define DIAG_REFORM_H

/*
 * This header is an attempt to reform the interfaces for diag3/ and diag4/
 * for the callbacks out to each architecture. The goal here is to be able to
 * (eventually) link both diag3/ and diag4/ simultaneously.
 */

#include <diag3/diagtypes1.h>

struct diag3_driver {
	diag_descriptor * (*NEW_DIAG_GLOBAL)(diag_descriptor *);
	void (*OUTPUT_GLOBALS_TAB)(void);
	void (*OUTPUT_DIAG_TAGS)(void);
	void (*INSPECT_FILENAME)(filename);
};

extern struct diag3_driver *diag3_driver;

#endif

