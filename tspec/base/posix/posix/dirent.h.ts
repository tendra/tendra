# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix/posix", "sys/types.h.ts" (?!) ;

+TYPE DIR, struct dirent ;
+NAT ~dirent_d_name_size ;
+FIELD struct dirent { char d_name [ ~dirent_d_name_size ] ; } ;

+FUNC int closedir ( DIR * ) ;
+FUNC DIR *opendir ( const char * ) ;
+FUNC struct dirent *readdir ( DIR * ) ;
+FUNC void rewinddir ( DIR * ) ;
