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


#ifndef INS_DATA
#define INS_DATA

#if USE_MY_INSTRUCTION_DATA
typedef char * Instruction_data;
#else
typedef struct{
    char *text;
    char *bindata;
} Instruction_data;

#define text(X) X.text
#define instruction_text(X) X.text
#define instruction_binasm(X) X.bindata
#define set_instruction_text(ins,instext) ins.text = instext
#define set_instruction_binasm(ins,dat) ins.bindata = dat
#endif

#endif
