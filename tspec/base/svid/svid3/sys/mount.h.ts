# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+CONST int MS_DATA, MS_RDONLY, MS_NOSUID, MS_REMOUNT ;

+FUNC int mount ( const char *, const char *, int, const char *,
		  const char *, int ) ;
+FUNC int umount ( const char * ) ;
