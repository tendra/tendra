/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FIND_ID_INCLUDED
#define FIND_ID_INCLUDED


extern Tagdec *tagdecs;
extern Tagdec *localdecs;
extern Tokdec *tokdecs;
extern Labdec *labdecs;
extern Al_tagdec *al_tagdecs;

extern Tagdec *find_tag(char *n);
extern Tokdec *find_tok(char *n);
extern Labdec *find_lab(char *n);
extern Al_tagdec *find_al_tag(char *n);
extern void tidy_labels(Labdec *old);


#endif
