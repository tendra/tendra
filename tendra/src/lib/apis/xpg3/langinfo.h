#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "xpg3", "nl_types.h" ;

+CONST nl_item D_T_FMT, D_FMT, T_FMT, AM_STR, PM_STR ;
+CONST nl_item DAY_1, DAY_2, DAY_3, DAY_4, DAY_5, DAY_6, DAY_7 ;
+CONST nl_item ABDAY_1, ABDAY_2, ABDAY_3, ABDAY_4, ABDAY_5, ABDAY_6, ABDAY_7 ;
+CONST nl_item MON_1, MON_2, MON_3, MON_4, MON_5, MON_6 ;
+CONST nl_item MON_7, MON_8, MON_9, MON_10, MON_11, MON_12 ;
+CONST nl_item ABMON_1, ABMON_2, ABMON_3, ABMON_4, ABMON_5, ABMON_6 ;
+CONST nl_item ABMON_7, ABMON_8, ABMON_9, ABMON_10, ABMON_11, ABMON_12 ;
+CONST nl_item RADIXCHAR, THOUSEP, YESSTR, NOSTR, CRNCYSTR ;

+FUNC char *nl_langinfo ( nl_item ) ;
