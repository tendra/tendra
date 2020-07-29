/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef STAGES_H
#define STAGES_H

#include "table.h"

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines perform the main compilation tasks, one routine corresponding
 * to each compilation phase. Each routine takes a list of input files and
 * returns a list of output files.
 */

extern filename *do_produce(filename *);
extern filename *do_preproc(filename *);
extern filename *do_cpp_produce(filename *);
extern filename *do_cpp_preproc(filename *);
extern filename *do_tdf_link(filename *);
extern filename *do_tdf_build(filename *);
extern filename *do_translate(filename *);
extern filename *do_assemble(filename *);
extern filename *do_dynlink(filename *);
extern filename *do_link(filename *);
extern filename *do_notation(filename *);
extern filename *do_pl_tdf(filename *);
extern filename *do_pretty(filename *);
extern filename *do_split_arch(filename *);
extern filename *do_build_arch(filename *);
extern filename *do_build_file(filename *, enum filetype);
extern filename *do_link_specs(filename *, enum filetype);
extern filename *do_cc(filename *, enum filetype);
extern filename *do_keep(filename *);

extern enum filetype binary_obj_type;


#endif /* STAGES_H */
