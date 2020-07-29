/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FETCH_H
#define FETCH_H


/*
    LOW-LEVEL DECODING ROUTINES
*/

void byte_align(void);
long fetch(int);
void rewind_posn(void);
long tell_posn(void);
void seek_posn(long);
void input_skip(long);


#endif /* FETCH_H */
