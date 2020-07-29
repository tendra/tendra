# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+NAT ~utsname_sysname_size ;
+NAT ~utsname_nodename_size ;
+NAT ~utsname_release_size ;
+NAT ~utsname_version_size ;
+NAT ~utsname_machine_size ;

+TYPE struct utsname ;
+FIELD struct utsname {
    char sysname [ ~utsname_sysname_size ] ;
    char nodename [ ~utsname_nodename_size ] ;
    char release [ ~utsname_release_size ] ;
    char version [ ~utsname_version_size ] ;
    char machine [ ~utsname_machine_size ] ;
} ;

+FUNC int uname ( struct utsname * ) ;
