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


/*  Definition of stack for maintaining isymMac and isymstart.

This is required because entries in the symbol table such as blocks,
procedures and files have two entries in the symbol table corresponding
to their beginning and end. The "start" entry has an associated index which
is the index of the "end" plus 1. The "end" entry has an associated index
which is the index of the "start". Consequently a stack of these indices
can be built up and an index is pushed when the start of a block, proc or
file is reached and popped when an end is reached. The routines for this are 
given in bstack.c */

#define STACKSIZE 100	


typedef struct stackdef {
		long symind [STACKSIZE];
		long strind [STACKSIZE];	/* space for stack elements */
		long pos;		/* current position of top of stack */
		struct stackdef * nextspace;	/* if more space required */
			} BSTACK;

/* An elemnt of the stack has the following type (result of popping a stack) */
typedef struct symstrdef	{long sym;
				long str;
				} SYMSTR;


extern void push PROTO_S ( ( long, long, BSTACK * ) ) ;
extern SYMSTR pop PROTO_S ( ( BSTACK * ) ) ;
