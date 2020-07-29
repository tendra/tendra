/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DE_UNIT_H
#define DE_UNIT_H


/*
    EQUATION DECODING ROUTINES
*/

extern int have_version;

void de_aldef(void);
void de_tagdec(void);
void de_tagdef(void);
void de_tokdec(void);
void de_tokdef(void);
void de_version(void);
void de_magic(char *);
void de_token_defn(construct *, node *);
construct *find_label(long);


#endif /* DE_UNIT_H */
