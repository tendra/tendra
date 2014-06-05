
/* TODO: possibly expand out inline. these aren't called from common/ */

#ifndef NEWDIAGS

#define DIAG_VAL_BEGIN(d,g,c,s,e)       \
                                stab_global (d, e, s, g);
#define DIAG_VAL_END(d)
#define DIAG_PROC_BEGIN(d,g,c,s,e)      \
                                stab_proc (d, e, s, g);
#define DIAG_PROC_END(d)
#define CODE_DIAG_INFO(d,n,x,a) code_diag_info (d, n, x, a);

#else

#define DIAG_VAL_BEGIN(d,g,c,s,e)   if (diag != DIAG_DWARF2)\
                  stab_global(d, e, s, g);

#define DIAG_VAL_END(d)

#define DIAG_PROC_BEGIN(d,g,c,s,e) if (diag == DIAG_DWARF2)\
                  dw2_proc_start(e, d);\
                else \
                  stab_proc(d, e, s, g);

#define DIAG_PROC_END(e)    if (diag == DIAG_DWARF2)\
                  dw2_proc_end(e);\
                else \
                  stab_proc_end();

#define CODE_DIAG_INFO(d,n,x,a) if (diag == DIAG_DWARF2)\
                  dw2_code_info(d, x, a);\
                else \
                  code_diag_info(d, x, a);


#define START_BB()      if (diag == DIAG_DWARF2)\
                  dw2_start_basic_block();

#endif

