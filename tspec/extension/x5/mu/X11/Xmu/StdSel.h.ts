# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "sys/types.h.ts", "caddr_t" (!?) ;
+USE "x5/t", "X11/Intrinsic.h.ts" ;

+FUNC Boolean XmuConvertStandardSelection ( Widget, Time, Atom *, Atom *,
    Atom *, caddr_t *, unsigned long *, int * ) ;
