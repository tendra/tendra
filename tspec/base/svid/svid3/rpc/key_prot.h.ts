# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_REMOTE_SERVICES %%

%%%
#include <sys/types.h>
#include <rpc/types.h>
#include <rpc/rpc.h>
#include <rpc/xdr.h>
%%%

+FUNC int getpublickey ( const char [], char [] ) ;
+FUNC int getsecretkey ( const char [], char [], const char * ) ;

+ENDIF
