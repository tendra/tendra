/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef COMPILE_INCLUDED
#define COMPILE_INCLUDED


/*
    MAIN COMPILATION ROUTINES

    The routines in this module are concerned with the main compilation
    actions of transforming declarations and definitions into TDF.
*/

extern void compile_variable(IDENTIFIER, int);
extern void compile_function(IDENTIFIER, int);
extern void compile_token(IDENTIFIER, int);
extern void compile_type(IDENTIFIER);
extern void compile_virtual(CLASS_TYPE, int);
extern void compile_asm(EXP);
extern void compile_comment(string, unsigned long);
extern void compile_preserve(IDENTIFIER);
extern void compile_pending(void);
extern void compile_weak(IDENTIFIER, IDENTIFIER);
extern void update_tag(IDENTIFIER, int);
extern LIST(IDENTIFIER)pending_funcs;

extern void enc_tagdec(IDENTIFIER, ulong, TYPE, int);
extern BITSTREAM *enc_tagdec_start(IDENTIFIER, ulong, TYPE, int);
extern void enc_tagdec_end(BITSTREAM *);
extern BITSTREAM *enc_tagdef_start(IDENTIFIER, ulong, TYPE, int);
extern void enc_tagdef_end(BITSTREAM *);
extern ulong make_tagdef(IDENTIFIER, TYPE, EXP, EXP, int);
extern BITSTREAM *enc_variable(BITSTREAM *, IDENTIFIER, int, EXP *, EXP);
extern BITSTREAM *enc_access(BITSTREAM *, DECL_SPEC);
extern BITSTREAM *enc_tokdef_start(ulong, const char *, ulong *, int);
extern void enc_tokdef_end(ulong, BITSTREAM *);
extern void enc_tokdec(ulong, const char *);
extern int enc_tokdef(IDENTIFIER, int);
extern void enc_dynamic_init(void);
extern DECL_SPEC crt_func_access;

#endif
