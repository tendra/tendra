# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "xpg3", "nl_types.h.ts" ;

+CONST nl_item D_T_FMT, D_FMT, T_FMT, AM_STR, PM_STR ;
+CONST nl_item DAY_1, DAY_2, DAY_3, DAY_4, DAY_5, DAY_6, DAY_7 ;
+CONST nl_item ABDAY_1, ABDAY_2, ABDAY_3, ABDAY_4, ABDAY_5, ABDAY_6, ABDAY_7 ;
+CONST nl_item MON_1, MON_2, MON_3, MON_4, MON_5, MON_6 ;
+CONST nl_item MON_7, MON_8, MON_9, MON_10, MON_11, MON_12 ;
+CONST nl_item ABMON_1, ABMON_2, ABMON_3, ABMON_4, ABMON_5, ABMON_6 ;
+CONST nl_item ABMON_7, ABMON_8, ABMON_9, ABMON_10, ABMON_11, ABMON_12 ;
+CONST nl_item RADIXCHAR, THOUSEP, YESSTR, NOSTR, CRNCYSTR ;

+FUNC char *nl_langinfo ( nl_item ) ;
