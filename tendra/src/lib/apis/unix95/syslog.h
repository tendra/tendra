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
+CONST int LOG_PID, LOG_CONS, LOG_NDELAY, LOG_ODELAY, LOG_NOWAIT ;

+CONST int LOG_KERN, LOG_USER, LOG_MAIL, LOG_NEWS, LOG_UUCP ;
+CONST int LOG_DAEMON, LOG_AUTH, LOG_CRON, LOG_LPR ;
+CONST int LOG_LOCAL0, LOG_LOCAL1, LOG_LOCAL2, LOG_LOCAL3 ;
+CONST int LOG_LOCAL4, LOG_LOCAL5, LOG_LOCAL6, LOG_LOCAL7 ;

+MACRO int LOG_MASK ( int ) ;
+MACRO int LOG_UPTO ( int ) ;

+CONST int LOG_EMERG, LOG_ALERT, LOG_CRIT, LOG_ERR ;
+CONST int LOG_WARNING, LOG_NOTICE, LOG_INFO, LOG_DEBUG ;

+FUNC void closelog ( void ) ;
+FUNC void openlog ( const char *, int, int ) ;
+FUNC int setlogmask ( int ) ;
+FUNC void syslog ( int, const char *, ... ) ;
