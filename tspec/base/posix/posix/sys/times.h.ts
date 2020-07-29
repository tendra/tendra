# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "time.h.ts", "clock_t" (!?) ;

+FIELD struct tms {
    clock_t tms_utime ;
    clock_t tms_stime ;
    clock_t tms_cutime ;
    clock_t tms_cstime ;
} ;

+FUNC clock_t times ( struct tms * ) ;
