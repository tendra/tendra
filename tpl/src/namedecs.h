/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef NAMEDECS_INCLUDED
#define NAMEDECS_INCLUDED

#include "units.h"


typedef struct{
	char *id;
	Name name;
} IdName;

typedef struct Sort_struct{
	int sort;
	struct Toksort_struct *toksort;
} Sort;
	/* sort of TOKEN is { token_sort , ptr to res and pars}
	   other sorts are  { X_sort, nil}
	 */


typedef struct Toksort_struct{
	Sort ressort;
	struct Tokpar_struct *pars;
} TokSort;
	/* if ressort is token then pars = nil */


typedef struct Tokpar_struct {
	Sort par;
	struct Tokpar_struct *next;
} Tokpar;


typedef struct Tokdec_struct {
	IdName idname;
	TokSort sort;
	struct Tokdec_struct *next;
	Bool isdeffed;
	Bool isused;
	Bool iskept;
	Bool isparam;
} Tokdec;

extern Tokdec *tokdecs;

typedef union {
	Name shtok;
	TDF tdfsh;
} Tagshape;

typedef struct Tagdec_struct {
	IdName idname;
	Bool isvar;
	Bool isdeffed;
	char hassh;
	Bool isused;
	Bool iskept;
	Bool iscommon;
	Tagshape sh;
	struct Tagdec_struct *next;
} Tagdec;

extern Tagdec *tagdecs;
extern Tagdec *localdecs;


typedef struct Al_tagdec_struct {
	IdName idname;
	struct Al_tagdec_struct *next;
	Bool isdeffed;
	Bool iskept;
	Bool isused;
} Al_tagdec;

extern Al_tagdec *al_tagdecs;

typedef struct Labdec_struct {
	IdName idname;
	Bool declared;
	struct Labdec_struct *next;
}  Labdec;

extern Labdec *labdecs;

extern Tokdec *find_tok(char *s);
extern Tagdec *find_tag(char *s);
extern Al_tagdec *find_al_tag(char *s);
extern Labdec *find_lab(char *s);

#define NEW_IDNAME(idn, s,ent)\
    (idn).id = s; (idn).name = next_name(ent);

#define LOCNAME(x)	(unsigned long)((x).name.unit_name)

#endif
