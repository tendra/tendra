/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef BUFFER_INCLUDED
#define BUFFER_INCLUDED


/*
    BUFFER PRINTING DECLARATIONS

    The routines in this module are concerned with the manipulation of
    character buffers.
*/

extern void free_buffer(BUFFER *);
extern BUFFER *clear_buffer(BUFFER *, FILE *);
extern void output_buffer(BUFFER *, int);
extern string extend_buffer(BUFFER *, string);
extern string stretch_buffer(BUFFER *, string, size_t);
extern size_t bfread(BUFFER *, string, size_t);
extern void bfprintf(BUFFER *, const char *, ...);
extern void bfputs(BUFFER *, string);
extern void bfputc(BUFFER *, int);


#endif
