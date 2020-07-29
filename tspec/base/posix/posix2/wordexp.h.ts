# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "c/c89", "stddef.h.ts", "size_t" (!?) ;

+FIELD ( struct ) wordexp_t {
    size_t we_wordc ;
    char **we_wordv ;
    size_t we_offs ;
} ;

+FUNC int wordexp ( const char *, wordexp_t *, int ) ;
+FUNC void wordfree ( wordexp_t * ) ;

+CONST int WRDE_APPEND, WRDE_DOOFFS, WRDE_NOCMD, WRDE_REUSE, WRDE_SHOWERR ;
+CONST int WRDE_UNDEF, WRDE_BADCHAR, WRDE_BADVAL, WRDE_CMDSUB ;
+CONST int WRDE_NOSPACE, WRDE_SYNTAX ;
+CONST int WRDE_NOSYS ;
