
/* TODO: possibly expand out inline. these aren't called from common/ */

#ifndef TDF_DIAG4

/* empty */

#else

#define DIAG_VAL_BEGIN(d,g,c,s)   if (diag != DIAG_DWARF2)\
                  out_diag_global(d, g, c, s);

#define DIAG_VAL_END(d)

#define DIAG_PROC_BEGIN(d,g,c,s,p) if (diag == DIAG_DWARF2)\
                  dw2_proc_start(p, d);\
                else \
                  diag_proc_begin(d, g, c, s);

#define DIAG_PROC_END(d,p)    if (diag == DIAG_DWARF2)\
                  dw2_proc_end(p);\
                else \
                  diag_proc_end();

#define CODE_DIAG_INFO(d,n,x,a) if (diag == DIAG_DWARF2)\
                  dw2_code_info(d, x, a);\
                else \
                  code_diag_info(d, x, a);


#define START_BB()      if (diag == DIAG_DWARF2)\
                  dw2_start_basic_block();

#endif

