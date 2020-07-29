/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PROCTYPES_INCLUDED
#define PROCTYPES_INCLUDED

#include <reader/exp.h>

#include <construct/installtypes.h>

typedef struct {
      int fixneeds  ;
      int floatneeds ;
      prop propneeds ;
      int maxargs ;
      int builtin;
      long sz;
} needs ;


#define wfixno		25
#define wfloatno	16

typedef struct {
    float fix [ wfixno ] ;
    float floating [ wfloatno ] ;
} weights ;


typedef struct {
    int regadd ;
    long stackadd ;
    long forweights ;
} parpair ;


typedef struct {
    long fixdump ;
    long fltdump ;
    long stack ;
} spacereq ;


typedef struct {
    needs needsproc ;
    spacereq spacereqproc ;
    long locals_space;
    long locals_offset;
    long callees_offset;
    long params_offset;
    int frame_sz;
    int max_args;
    int fixdump;
    int floatdump;
    int dumpstart;
    int fldumpstart;
    int callee_sz;
    exp nameproc ;
    int tlrecstart ;
    int expproc ;
    bool Has_ll;
    bool Has_checkalloc;
    bool has_vcallees;
    bool has_no_vcallers;
    bool leaf;
    bool Has_alloca;  
} procrec ;


typedef struct {
    weights wp_weights ;
    long fix_break ;
    long float_break ;
} wp ;


typedef struct {
    long fixed ;
    long flt ;
} space  ;



extern procrec *procrecs ;

#endif /* PROCTYPES_INCLUDED */










