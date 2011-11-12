/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef STARTUP_H
#define STARTUP_H


/*
 * PROCEDURE DECLARATIONS
 *
 * These procedures are concerned with the tcc startup and endup files.
 */

extern void add_to_startup(const char *fmt, ...);
extern void add_to_endup(const char *fmt, ...);
extern void close_startup(void);
extern void remove_startup(void);
extern void add_pragma(const char *);
extern void add_token(const char *);


/*
 * COMMAND-LINE OPTIONS
 *
 * These variables give the command-line options necessary to pass the startup
 * and endup files to the producer.
 */

extern char *startup_opt, *endup_opt;
extern char *tokdef_name;


#endif /* STARTUP_H */
