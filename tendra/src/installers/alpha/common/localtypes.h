/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef localtypes_key
#define localtypes_key 1

#include "exptypes.h"

struct asht {			/* structure definition for ash  */
  int  ashsize;	/*  the minimum size in bits of a shape  
				*/
  int  ashalign;      	/* the required alignment in bit units of
				   the start of a shape */
};

typedef struct asht ash;

extern ash ashof PROTO_S ((shape s));

struct specit {
  bool is_special;
  exp special_exp;
};
typedef struct specit speci;



#endif
