/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
