/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_C_OUTPUT_H
#define LEXI_C_OUTPUT_H

struct ast;
struct options;

/*
 * This routine is the entry point for the main output routine.
 *
 * This interface provides support for generating code for both C90 and C99.
 * There are slight differences in the generates APIs between the two (for
 * example, C99 provides <stdbool.h>), but otherwise they remain similar
 * enough to roll together into one interface; the generated code produces
 * both, and which is applicable is selected by #if on __STDC_VERSION__
 * at compile time.
 */
void
c_out_all(struct options *opt, struct ast *ast);

#endif

